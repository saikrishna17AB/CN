#include<iostream>
using namespace std;

#include<chrono>
#include<windows.h>
#include<thread>
#include<cstdlib>
#include<ctime>

int transmissiondelay = 1000;
int ackdelay = 1000;
int timeout = 3000;


void sendframe(int frameno)
{
    cout << "Sending frame: " << frameno << endl;
    Sleep(transmissiondelay);
}


void receiveframe(int frameno)
{
    cout << "Frame received: " << frameno << endl;
}


void sendack(int frameno)
{
    cout << "Sending acknowledgement for frame: "
         << frameno << endl;

    Sleep(ackdelay);
}


void receiveack(int ackno)
{
    cout << "Sender received ACK: "
         << ackno << endl;
}


void showwindow(int base, int windowsize, int totalframes)
{
    cout << "Current window: ";

    for(int i = base;
        i < base + windowsize && i < totalframes;
        i++)
    {
        cout << i << " ";
    }

    cout << "\n\n";
}


int main()
{
    srand(time(0));

    int totalframes = 8;
    int windowsize = 4;

    int base = 0;

    // Stores whether each frame has been successfully ACKed
    bool acknowledged[totalframes] = {false};

    while(base < totalframes)
    {
        cout << "\n====================================\n";

        showwindow(base, windowsize, totalframes);

        for(int i = base;
            i < base + windowsize && i < totalframes;
            i++)
        {
            // Do not send a frame again if it is already ACKed
            if(acknowledged[i])
                continue;

            sendframe(i);

            // Random frame loss
            int framelost = rand() % 5;

            if(framelost == 0)
            {
                cout << "Frame lost: " << i << endl;
            }
            else
            {
                receiveframe(i);

                // Receiver immediately ACKs the
                // successfully received frame
                sendack(i);

                receiveack(i);

                acknowledged[i] = true;
            }

            cout << endl;
        }


        int oldbase = base;

        while(base < totalframes && acknowledged[base])
        {
            base++;
        }

        if(base == oldbase)
        {
            cout << "Waiting for lost frame..." << endl;

            Sleep(timeout);

            cout << "TIMEOUT!" << endl;
            
            // Selective Repeat:
            // Only retransmit the unacknowledged frames.
            // Already ACKed frames are NOT retransmitted.

            for(int i = base;
                i < base + windowsize && i < totalframes;
                i++)
            {
                if(!acknowledged[i])
                {
                    cout << "\nRetransmitting frame: "
                         << i << endl;

                    sendframe(i);

                    // Assume retransmitted frame reaches receiver
                    receiveframe(i);

                    sendack(i);
                    receiveack(i);

                    acknowledged[i] = true;
                }
            }

            // Move window after retransmissions
            while(base < totalframes && acknowledged[base])
            {
                base++;
            }
        }
    }

    cout << "\nAll frames transmitted successfully." << endl;

    return 0;
}