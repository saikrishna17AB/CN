#include <stdio.h>      
#include <stdlib.h>     
#include <fcntl.h>      
#include <unistd.h>     

int main(){
    int fd = open("traffic_fifo", O_RDONLY);

    if (fd == -1){
        perror("open");
        exit(1);
    }

    // Create a variable to store the command
    char command[50];

    // Read command from FIFO
    read(fd, command, sizeof(command));

    printf("Command received: %s\n", command);

    // Display the final signal status
    printf("\n>>> %s <<<\n", command);

    close(fd);

    return 0;
}