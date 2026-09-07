#include <stdio.h>         
#include <stdlib.h>         
#include <sys/ipc.h>        
#include <sys/shm.h>        
#include <unistd.h>         

// Structure to store traffic information
struct TrafficData{
    int north;              // Vehicles in North direction
    int south;              // Vehicles in South direction
    int east;               // Vehicles in East direction
    int west;               // Vehicles in West direction
};

int main(){
    // Generate a key for shared memory
    key_t key = ftok("trafficsensor.c", 65);

    // Check if key generation failed
    if (key == -1){
        perror("ftok");
        exit(1);
    }

    // Create shared memory
    int shmid = shmget(key,sizeof(struct TrafficData),0666 | IPC_CREAT);

    // Check if shared memory creation failed
    if (shmid == -1){
        perror("shmget");
        exit(1);
    }

    // Attach shared memory to this process
    struct TrafficData *traffic =(struct TrafficData *)shmat(shmid, NULL, 0);

    // Check if attachment failed
    if (traffic == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    printf("\nTRAFFIC SENSOR\n");

    //North traffic
    printf("Enter vehicles in North: ");
    scanf("%d", &traffic->north);

    //South traffic
    printf("Enter vehicles in South: ");
    scanf("%d", &traffic->south);

    //East traffic
    printf("Enter vehicles in East: ");
    scanf("%d", &traffic->east);

    //West traffic
    printf("Enter vehicles in West: ");
    scanf("%d", &traffic->west);

    // Display the information stored in shared memory
    printf("\nTraffic information stored!\n");

    printf("North : %d\n", traffic->north);
    printf("South : %d\n", traffic->south);
    printf("East  : %d\n", traffic->east);
    printf("West  : %d\n", traffic->west);

    // Detach shared memory
    shmdt(traffic);

    return 0;
}