#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/select.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define TOTALSLOTS 10

struct ParkingData{
    int totalslots;
    int occupiedslots;
    int avaliableslots;
    int vehiclesentering;
    int vehiclesleaving;

    int lastallocatedslot;
    int slotstatus[TOTALSLOTS+1]
};

//Representing the gates as processes

pid_t gatepids[3];
pid_t exitpid;
pid_t monitorpid;

//Shared memory

int shmid;
struct ParkingData* parking;

int requestfd;
int exitfd;
int gatefd[3];

int findfreeslot(){
    for(int i=1;i<=TOTALSLOTS;i++){
        if(parking->slotstatus[i]==0){
            return i;
        }
    }
    return -1;
}

int allocateslot(){
    int slot=findfreeslot();
    if(slot==-1){
        return -1;
    }

    parking->slotstatus[slot]=1;
    parking->occupiedslots+=1;
    parking->avaliableslots-=1;
    parking->vehiclesentering+=1;
    parking->lastallocatedslot=slot;
    return slot;

}

//Free a parking slot

int freeslot(int slot){
    if(slot<1 || slot>TOTALSLOTS){
        return -1;
    }
    if(parking->slotstatus[slot]==0){
        return 0;
    }
    parking->slotstatus[slot]=0;
    parking->occupiedslots-=1;
    parking->avaliableslots+=1;
    parking->vehiclesleaving+=1;
    
    return 1;
}

//Send a response to a particular gate

void sendgateresponse(int gate,const char *message){
    if(gate<1 || gate>3){
        return;
    }
    write(gatefd[gate-1],message,strlen(message)+1);

}

//Process a gate request


//Process a gate request

void processgaterequest(char *request){

    int gate;

    if(sscanf(request,"GATE%d REQUEST",&gate)!=1){
        printf("Invalid gate request: %s\n",request);
        return;
    }

    printf("Controller: Request received from Gate %d\n",gate);

    //Check if parking is full

    if(parking->avaliableslots==0){

        char response[100];

        snprintf(response,
                 sizeof(response),
                 "GATE%d DENY PARKING_FULL",
                 gate);

        sendgateresponse(gate,response);

        printf("Controller: Gate %d denied - parking full\n",gate);

        return;
    }

    //Allocate a slot

    int slot=allocateslot();

    if(slot==-1){

        char response[100];

        snprintf(response,
                 sizeof(response),
                 "GATE%d DENY PARKING_FULL",
                 gate);

        sendgateresponse(gate,response);

        return;
    }

    //Send approval to gate

    char response[100];

    snprintf(response,
             sizeof(response),
             "GATE%d ALLOW SLOT=%d",
             gate,
             slot);

    sendgateresponse(gate,response);

    printf("Controller: Gate %d allowed - Slot %d\n",gate,slot);

    printf("Occupied slots: %d\n",
           parking->occupiedslots);

    printf("Available slots: %d\n",
           parking->avaliableslots);
}

//Process vehicle exit

void processexit(char *message){

    int slot;

    if(sscanf(message,"EXIT SLOT=%d",&slot)!=1){
        printf("Invalid exit request: %s\n",message);
        return;
    }

    printf("Controller: Exit request for Slot %d\n",slot);

    int result=freeslot(slot);

    if(result==1){

        printf("Controller: Slot %d is now free\n",slot);

        printf("Occupied slots: %d\n",
               parking->occupiedslots);

        printf("Available slots: %d\n",
               parking->avaliableslots);
    }
    else if(result==0){

        printf("Controller: Slot %d is already free\n",slot);
    }
    else{

        printf("Controller: Invalid slot number %d\n",slot);
    }
}

//Cleanup

void cleanup(int signalnumber){

    printf("\nController: Cleaning up...\n");

    //Terminate gate processes

    for(int i=0;i<3;i++){
        if(gatepids[i]>0){
            kill(gatepids[i],SIGTERM);
        }
    }

    //Terminate exit process

    if(exitpid>0){
        kill(exitpid,SIGTERM);
    }

    //Terminate monitor process

    if(monitorpid>0){
        kill(monitorpid,SIGTERM);
    }

    //Close file descriptors

    if(requestfd>=0){
        close(requestfd);
    }

    if(exitfd>=0){
        close(exitfd);
    }

    for(int i=0;i<3;i++){
        if(gatefd[i]>=0){
            close(gatefd[i]);
        }
    }

    //Remove FIFOs

    unlink("request_fifo");
    unlink("exit_fifo");

    unlink("gate1_fifo");
    unlink("gate2_fifo");
    unlink("gate3_fifo");

    //Detach shared memory

    if(parking!=(void *)-1){
        shmdt(parking);
    }

    //Remove shared memory

    if(shmid>=0){
        shmctl(shmid,IPC_RMID,NULL);
    }

    printf("Controller: Cleanup complete\n");

    exit(0);
}

int main(){


    printf("SMART PARKING CONTROLLER\n");


    //Register cleanup

    signal(SIGINT,cleanup);
    signal(SIGTERM,cleanup);

    //Create shared memory

    shmid=shmget(1234,
                 sizeof(struct ParkingData),
                 IPC_CREAT | 0666);

    if(shmid==-1){
        perror("shmget");
        exit(1);
    }

    //Attach shared memory

    parking=(struct ParkingData *)shmat(shmid,NULL,0);

    if(parking==(void *)-1){
        perror("shmat");
        shmctl(shmid,IPC_RMID,NULL);
        exit(1);
    }

    //Initialize parking information

    parking->totalslots=TOTALSLOTS;
    parking->occupiedslots=0;
    parking->avaliableslots=TOTALSLOTS;

    parking->vehiclesentering=0;
    parking->vehiclesleaving=0;

    parking->lastallocatedslot=0;

    for(int i=0;i<=TOTALSLOTS;i++){
        parking->slotstatus[i]=0;
    }

    //Remove old FIFOs if they exist

    unlink("request_fifo");
    unlink("exit_fifo");

    unlink("gate1_fifo");
    unlink("gate2_fifo");
    unlink("gate3_fifo");

    //Create FIFOs

    if(mkfifo("request_fifo",0666)==-1){
        perror("mkfifo request_fifo");
        cleanup(0);
    }

    if(mkfifo("exit_fifo",0666)==-1){
        perror("mkfifo exit_fifo");
        cleanup(0);
    }

    if(mkfifo("gate1_fifo",0666)==-1){
        perror("mkfifo gate1_fifo");
        cleanup(0);
    }

    if(mkfifo("gate2_fifo",0666)==-1){
        perror("mkfifo gate2_fifo");
        cleanup(0);
    }

    if(mkfifo("gate3_fifo",0666)==-1){
        perror("mkfifo gate3_fifo");
        cleanup(0);
    }

    //Open FIFOs

    requestfd=open("request_fifo",O_RDWR);

    if(requestfd==-1){
        perror("open request_fifo");
        cleanup(0);
    }

    exitfd=open("exit_fifo",O_RDWR);

    if(exitfd==-1){
        perror("open exit_fifo");
        cleanup(0);
    }

    gatefd[0]=open("gate1_fifo",O_RDWR);
    gatefd[1]=open("gate2_fifo",O_RDWR);
    gatefd[2]=open("gate3_fifo",O_RDWR);

    for(int i=0;i<3;i++){
        if(gatefd[i]==-1){
            perror("open gate fifo");
            cleanup(0);
        }
    }

    //Create Gate 1, Gate 2 and Gate 3

    for(int i=0;i<3;i++){

        gatepids[i]=fork();

        if(gatepids[i]<0){
            perror("fork");
            cleanup(0);
        }

        if(gatepids[i]==0){

            char gatenumber[10];

            snprintf(gatenumber,
                     sizeof(gatenumber),
                     "%d",
                     i+1);

            execl("./gate",
                  "./gate",
                  gatenumber,
                  NULL);

            perror("execl gate");
            exit(1);
        }
    }

    //Create Exit Process

    exitpid=fork();

    if(exitpid<0){
        perror("fork");
        cleanup(0);
    }

    if(exitpid==0){

        execl("./exit_process",
              "./exit_process",
              NULL);

        perror("execl exit_process");
        exit(1);
    }

    //Create Monitor Process

    monitorpid=fork();

    if(monitorpid<0){
        perror("fork");
        cleanup(0);
    }

    if(monitorpid==0){

        execl("./monitor",
              "./monitor",
              NULL);

        perror("execl monitor");
        exit(1);
    }

    printf("Controller: All processes created\n");
    printf("Controller: Waiting for requests...\n");

    //Controller loop

    while(1){

        fd_set readfds;

        FD_ZERO(&readfds);

        FD_SET(requestfd,&readfds);
        FD_SET(exitfd,&readfds);

        int maxfd=requestfd;

        if(exitfd>maxfd){
            maxfd=exitfd;
        }

        /*
           Wait for either a gate request
           or an exit request
        */

        int result=select(maxfd+1,
                          &readfds,
                          NULL,
                          NULL,
                          NULL);

        if(result==-1){

            if(errno==EINTR){
                continue;
            }

            perror("select");
            break;
        }

        //Gate request

        if(FD_ISSET(requestfd,&readfds)){

            char request[100];

            int bytesread=read(requestfd,
                               request,
                               sizeof(request)-1);

            if(bytesread>0){

                request[bytesread]='\0';

                processgaterequest(request);
            }
        }

        //Exit request

        if(FD_ISSET(exitfd,&readfds)){

            char message[100];

            int bytesread=read(exitfd,
                               message,
                               sizeof(message)-1);

            if(bytesread>0){

                message[bytesread]='\0';

                processexit(message);
            }
        }
    }

    cleanup(0);

    return 0;
}
