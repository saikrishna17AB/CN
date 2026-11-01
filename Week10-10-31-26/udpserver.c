#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

int main(){
    int serversocket,clientsocket;
    struct sockaddr_in serveraddress,clientaddress;

    char buffer[1024];
    char response[1024];

    socklen_t addrlen=sizeof(clientaddress);
    serversocket=socket(AF_INET,SOCK_DGRAM,0);
    if(serversocket<0){
        printf("Socket allocation failed\n");
        return 0;
    }

    serveraddress.sin_family=AF_INET;
    serveraddress.sin_port=htons(8000);
    serveraddress.sin_addr.s_addr=INADDR_ANY;

    if(bind(serversocket,(struct sockaddr *)&serveraddress,sizeof(serveraddress))<0){
        printf("Bind failed\n");
        close(serversocket);
        return 0;
    }

    printf("Waiting for client message...\n");

    int n=recvfrom(serversocket,buffer,sizeof(buffer)-1,0,(struct sockaddr *)&clientaddress, &addrlen);

    if(n<0){
        printf("Message receiving failed\n");
        close(serversocket);
        return 0;

    }

    buffer[n]='\0';

    printf("Hamming code received : %s\n",buffer);
    if(strlen(buffer)!=7 || strspn(buffer,"01")!=7){
        strcpy(response,"INVALID INPUT");
    }

    if(n>0){
        int b[8];
        for(int i=1;i<=7;i++){
            b[i]=buffer[i-1]-'0';
        }

        int p1=b[1]^b[3]^b[5]^b[7];
        int p2=b[2]^b[3]^b[6]^b[7];
        int p4=b[4]^b[5]^b[6]^b[7];

        int parity=(p1)+(p2*2)+(p4*4);

        if(parity==0){
            strcpy(response,"GOOD DATA");
        }
        else{
            strcpy(response,"BAD DATA");
            printf("Partity: %d\n",parity);
        }
    }

    int sent=sendto(serversocket,response,strlen(response)+1,0,(struct sockaddr *)&clientaddress,addrlen);
    if(sent<0){
        printf("Send failed\n");
        close(serversocket);
        return 0;
    }
    close(serversocket);
    return 0;

    




}