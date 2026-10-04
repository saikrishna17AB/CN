#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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


    while(1){

    
        printf("PARKING STATUS\n");
       

        printf("Total slots     : %d\n",
               parking->totalslots);

        printf("Occupied slots  : %d\n",
               parking->occupiedslots);

        printf("Available slots : %d\n",
               parking->avaliableslots);

        printf("Vehicles entered: %d\n",
               parking->vehiclesentering);

        printf("Vehicles left   : %d\n",
               parking->vehiclesleaving);

        printf("Last allocated  : %d\n",
               parking->lastallocatedslot);


        printf("\nSlot Status:\n");

        for(int i=1;i<=TOTALSLOTS;i++){

            if(parking->slotstatus[i]==1){
                printf("Slot %d : Occupied\n",i);
            }
            else{
                printf("Slot %d : Free\n",i);
            }
        }

      

        sleep(4);
    }


    shmdt(parking);

    return 0;
}