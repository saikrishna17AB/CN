#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

int main(){
    int serversocket,clientsocket;
    struct sockaddr_in serveraddress;
    
    char buffer[1024];
    char response[1024];

    // Establish the connection
    serversocket=socket(AF_INET,SOCK_STREAM,0);
    if(serversocket<0){
        printf("Socket not initialized");
        return 0;
    }

    //Initalize the IP address and port

    serveraddress.sin_family=AF_INET;
    serveraddress.sin_port=htons(8000);
    serveraddress.sin_addr.s_addr=INADDR_ANY;

    //Bind the socket to IP and port

    if(bind(serversocket,(struct sockaddr *)&serveraddress,sizeof(serveraddress))<0){
        printf("Bind failed");
        close(serversocket);
        return 1;
    }

    //Listen for connection

    listen(serversocket,5);
    printf("Server waiting for clinet\n");

    //Accept clients conenction

    clientsocket=accept(serversocket,NULL,NULL);

    if(clientsocket<0){
        printf("Connection failed");
        close(serversocket);
        return 1;
    }

    printf("Client connection successful\n");

    //Receive hamming code from the client

    int n=recv(clientsocket,buffer,sizeof(buffer)-1,0);

    if(n>0){
        buffer[n]='\0';
        
        printf("Hamming code received : %s\n",buffer);
        if(strlen(buffer)!=7 || strspn(buffer,"01")!=7){
            strcpy(response,"INVALID INPUT");
        }
        else{
            //Hamming code is valid check
            int b[8];
            for(int i=1;i<=7;i++){
                b[i]=buffer[i-1]-'0';
            }
            

            int p1=b[1]^b[3]^b[5]^b[7];
            int p2=b[2]^b[3]^b[5]^b[6];
            int p4=b[4]^b[5]^b[6]^b[7];

            int syndrome=p1 + (p2*2) + (p4*4);
            printf("Syndrome: %d\n",syndrome);
            if(syndrome==0){
                strcpy(response,"GOOD DATA");
            }
            else{
                strcpy(response,"BAD DATA");
            }
        }

        //Send the response to the client
        send(clientsocket,response,sizeof(response),0);
    }

    //Close the connection

    close(clientsocket);
    close(serversocket);

    return 0;

}