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

    socklen_t addrlen=sizeof(serveraddress);
    clientsocket=socket(AF_INET,SOCK_DGRAM,0);
    
    if(clientsocket<0){
        printf("Socket establish failed\n");
        return 0;
    }

    serveraddress.sin_family=AF_INET;
    serveraddress.sin_port=htons(8000);
    serveraddress.sin_addr.s_addr=inet_addr("127.0.0.1");

    //Send the message to the address of the server

    printf("Enter the hamming code:\n");
    scanf("%s",hammingcode);

    int send=sendto(clientsocket,hammingcode,sizeof(hammingcode)+1,0,(struct sockaddr *)&serveraddress, sizeof(serveraddress));

    if(send<0){
        printf("Send failed");
        close(clientsocket);
        return 0;
    }
    //Receive the message
    int n=recvfrom(clientsocket,buffer,sizeof(buffer)-1,0,(struct sockaddr *)&serveraddress, &addrlen);

    if(n<0){
        printf("message recieving failed");
        close(clientsocket);
        return 0;
    }
    buffer[n]='\0';

    printf("Message recieved from server: %s\n",buffer);

    close(clientsocket);
    return 0;







}