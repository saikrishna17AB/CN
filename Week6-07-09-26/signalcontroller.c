#include <stdio.h>          
#include <stdlib.h>         
#include <sys/ipc.h>        
#include <sys/shm.h>        
#include <sys/stat.h>       
#include <fcntl.h>          
#include <unistd.h>         

struct TrafficData{
    int north;              // North vehicle count
    int south;              // South vehicle count
    int east;               // East vehicle count
    int west;               // West vehicle count
};

int main()
{
    // Generate the same key used by the sensor
    key_t key = ftok("trafficsensor.c", 65);

    // Check for error
    if (key == -1){
        perror("ftok");
        exit(1);
    }

    // Get the existing shared memory
    int shmid = shmget(key,sizeof(struct TrafficData),0666);

    // Check whether shared memory exists
    if (shmid == -1){
        perror("shmget");
        printf("Please run the sensor first.\n");
        exit(1);
    }

    // Attach shared memory
    struct TrafficData *traffic =
        (struct TrafficData *)shmat(shmid, NULL, 0);

    // Check for attachment error
    if (traffic == (void *)-1){
        perror("shmat");
        exit(1);
    }

    // Create the FIFO
    mkfifo("traffic_fifo", 0666);

    printf("\nSIGNAL CONTROLLER\n");

    // Display traffic information
    printf("\nTraffic Information:\n");

    printf("North : %d vehicles\n", traffic->north);
    printf("South : %d vehicles\n", traffic->south);
    printf("East  : %d vehicles\n", traffic->east);
    printf("West  : %d vehicles\n", traffic->west);

    // Assume North has the highest traffic initially
    int max_traffic = traffic->north;

    // Store the direction
    char direction[10] = "NORTH";

    if (traffic->south > max_traffic){
        max_traffic = traffic->south;

    
        snprintf(direction, sizeof(direction), "SOUTH");
    }

    if (traffic->east > max_traffic)
    {
        max_traffic = traffic->east;

        snprintf(direction, sizeof(direction), "EAST");
    }

    if (traffic->west > max_traffic){
        max_traffic = traffic->west;

        // Change direction to West
        snprintf(direction, sizeof(direction), "WEST");
    }

    // Create the signal command
    char command[50];

    snprintf(command,sizeof(command),"GREEN %s",direction);


    printf("Highest traffic : %d vehicles\n", max_traffic);

    printf("Signal command  : %s\n", command);

    printf("\nSending command through FIFO...\n");

    int fd = open("traffic_fifo", O_WRONLY);

    // Check for error
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    // Send command through FIFO
    write(fd, command, sizeof(command));

    close(fd);

    // Detach shared memory
    shmdt(traffic);

    return 0;
}