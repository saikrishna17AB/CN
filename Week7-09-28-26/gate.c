#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char *argv[])
{
    if(argc!=2){
        printf("Gate number not provided\n");
        return 1;
    }

    int gatenumber=atoi(argv[1]);

    char requestfifo[50];
    char responsefifo[50];

    snprintf(requestfifo,
             sizeof(requestfifo),
             "request_fifo");

    snprintf(responsefifo,
             sizeof(responsefifo),
             "gate%d_fifo",
             gatenumber);

    int requestfd=open(requestfifo,O_WRONLY);

    if(requestfd==-1){
        perror("open request_fifo");
        return 1;
    }

    int responsefd=open(responsefifo,O_RDONLY);

    if(responsefd==-1){
        perror("open gate fifo");
        close(requestfd);
        return 1;
    }

    while(1){

        char request[100];

        snprintf(request,
                 sizeof(request),
                 "GATE%d REQUEST",
                 gatenumber);

        write(requestfd,
              request,
              strlen(request)+1);

        printf("Gate %d: Request sent\n",
               gatenumber);


        char response[100];

        int bytesread=read(responsefd,
                           response,
                           sizeof(response)-1);

        if(bytesread>0){

            response[bytesread]='\0';

            printf("Gate %d: %s\n",
                   gatenumber,
                   response);
        }

        sleep(3);
    }

    close(requestfd);
    close(responsefd);

    return 0;
}    