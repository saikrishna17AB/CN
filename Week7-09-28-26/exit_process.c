#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define TOTALSLOTS 10

struct ParkingData{
    int totalslots;
    int occupiedslots;
    int avaliableslots;
    int vehiclesentering;
    int vehiclesleaving;

    int lastallocatedslot;
    int slotstatus[TOTALSLOTS+1];
};

int main()
{
    int shmid;

    struct ParkingData *parking;


    //Attach to existing shared memory

    shmid=shmget(1234,
                 sizeof(struct ParkingData),
                 0666);

    if(shmid==-1){
        perror("shmget");
        return 1;
    }


    parking=(struct ParkingData *)shmat(shmid,
                                         NULL,
                                         0);

    if(parking==(void *)-1){
        perror("shmat");
        return 1;
    }


    //Open exit FIFO

    int exitfd=open("exit_fifo",O_WRONLY);

    if(exitfd==-1){
        perror("open exit_fifo");
        shmdt(parking);
        return 1;
    }


    while(1){

    
         //  Find an occupied slot.

        int slot=-1;

        for(int i=1;i<=TOTALSLOTS;i++){

            if(parking->slotstatus[i]==1){

                slot=i;
                break;
            }
        }


        if(slot!=-1){

            char message[100];

            snprintf(message,
                     sizeof(message),
                     "EXIT SLOT=%d",
                     slot);

            write(exitfd,
                  message,
                  strlen(message)+1);

            printf("Exit Process: %s\n",
                   message);
        }
        else{

            printf("Exit Process: No occupied slot\n");
        }


        sleep(5);
    }


    close(exitfd);

    shmdt(parking);

    return 0;
}