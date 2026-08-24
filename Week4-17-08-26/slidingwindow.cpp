#include<iostream>
using namespace std;
#include<chrono>
#include<windows.h>
#include<thread>
#include<cstdlib>
#include<ctime>
int totalframes=5;
int timeout=3000;
int tranmissiondelay=1000;
int ackdelay=1000;

void sendframe(int frameno){
    cout<<"Sending frame: "<<frameno<<" "<<endl;
    Sleep(tranmissiondelay);
}
void receiveframe(int frameno){
    
    // int lost=rand()%5;
    // if(lost==0){
    //     cout<<"Frame lost "<<frameno<<" ";
    //     cout<<"TIMEOUT "<<endl;
    //     Sleep(timeout);
    //     cout<<"Sender retransmitting frame: "<<frameno<<endl;
    //     sendframe(frameno);
    // }
    
        cout<<"Frame received "<<frameno<<" "<<endl;
}

void sendack(int frameno){
    cout<<"Sending acknowledgement for "<<frameno<<" "<<endl;
    // int acklost=rand()%5;
    // Sleep(ackdelay);
    // if(acklost==0){
    //         cout<<"Acknowledgemt lost "<<frameno<<endl;
    //         Sleep(timeout);

    //         cout<<"Acknowledgement not recieved... "<<endl;
            
    //         cout<<"Retransmitting frame: "<<frameno<<endl;
    //         sendframe(frameno);
    // }
       
    Sleep(ackdelay);
}
void receiveack(int ackno){
    cout << "Sender received ACK " << ackno << endl;
}

void showwindow(int base,int windowsize,int totalframes){
    for(int i=base;i<base+windowsize && i<totalframes;i++){
            cout<<i<<" ";
        }
    cout<<"\n\n";
}

int main(){
    int totalframes=8;
    int windowsize=4;

    int base=0;
    while(base<totalframes){
        cout<<"Current window :"<<endl;
        showwindow(base, windowsize, totalframes);

        int firstlostframe=-1;

        for(int i=base;i<base+windowsize && i<totalframes;i++){
            sendframe(i);

            int framelost=rand()%5;
            if(framelost==0){
                cout<<"Frame lost "<<i<<endl;
                if(firstlostframe==-1){
                    firstlostframe=i;
                }
            }
            else{
                receiveframe(i);
            }
            cout<<endl;
        }

        //Receiver sends acknowldegement
        //If a frame is lost, the reciver cannot acknowledge frames after the frame is lost

        if(firstlostframe==-1){
            int lastframe=base+windowsize-1;

            if(lastframe>=totalframes){
                lastframe=totalframes-1;
            }
            sendack(lastframe);
            receiveack(lastframe);

            base=lastframe+1;

        }
        else{


            if (firstlostframe > base) {
                int ackNo = firstlostframe - 1;

                sendack(ackNo);
                receiveack(ackNo);
                
            }
            cout<<"Waiting for ACK"<<endl;
            
            
            Sleep(timeout);

            cout << "Sender: TIMEOUT!" << endl;

            cout << "Sender: Go-Back-N triggered." << endl;

            cout << "Sender: Going back to Frame "<< firstlostframe << endl;

            /*
                Move the window back to the first
                lost frame.

                Frames from this point onward
                will be retransmitted.
            */

            base = firstlostframe;
        }

    }
    return 0;
    
}