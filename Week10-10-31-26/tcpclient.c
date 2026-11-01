#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

int main(){
    int clientsocket;
    struct sockaddr_in serveraddress;

    char buffer[1024];
    char hammingcode[1024];

    clientsocket=socket(AF_INET,SOCK_STREAM,0);
    if(clientsocket<0){
        printf("Socket estanlishment failed");
        return 1;
    }

    serveraddress.sin_family=AF_INET;
    serveraddress.sin_port=htons(8000);
    serveraddress.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(clientsocket,(struct sockaddr *)&serveraddress,sizeof(serveraddress))<0){
        printf("Connection failed, cannot connect to server");
        close(clientsocket);
        return 1;
    }

    printf("Connected to server");

    //Send message to the server

    printf("Enter the Hamming code: \n");
    scanf("%s",hammingcode);

    send(clientsocket,hammingcode,sizeof(hammingcode),0);

    //Receive message from the server
    int n=recv(clientsocket,buffer,sizeof(buffer)-1,0);

    if(n>0){
        buffer[n]='\0';
        printf(buffer);
    }

    close(clientsocket);
    return 1;

    
}