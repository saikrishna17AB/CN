#include<iostream>
using namespace std;
#include<chrono>
#include<windows.h>
#include<thread>
#include<cstdlib>
#include<ctime>
int main(){
    int totalframes=5;
    int timeout=3000;
    int tranmissiondelay=1000;
    int ackdelay=1000;

    srand(time(0));
    int frame=0;
    
    while(frame<totalframes){
        int seqno=frame%2;
        
        cout<<"Sender sending frame "<<frame<<endl;
        Sleep(tranmissiondelay);
        
        int framelost=rand()%5;
        if(framelost==0){
            cout<<" frame lost "<<endl;
            Sleep(timeout);
            cout<<"TIMEOUT! "<<endl;
            cout<<"Sender retransmitting frame: "<<frame<<endl;
            continue;
        }
        cout<<"Received frame: "<<frame<<" received : "<<seqno<<endl;

        
        cout<<"Receivier sending acknowldegement for frame: "<<frame<<" "<<seqno<<endl;
        Sleep(ackdelay);

        int acklost=rand()%5;
        if(acklost==0){
            cout<<"Acknowledgemt lost "<<seqno<<endl;
            Sleep(timeout);

            cout<<"Acknowledgement not recieved... "<<endl;
            
            cout<<"Retransmitting frame: "<<frame<<endl;
            continue;
        }

        //Acknowledement recieved
        cout<<"Acknowledgement received for frame"<<seqno<<" Frame: "<<frame<<endl;
        frame++;

    }
    return 0;
}