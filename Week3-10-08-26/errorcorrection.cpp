#include<iostream>
#include<cmath>
#include<string>
using namespace std;

int main(){
    string data="1011";

    //m - data bits
    //r - parity bits

    int m=data.length();
    int r=0;
    while(pow(2,r)<(m+r+1)){
        r++;
    }

    //Total bits
    int n=m+r;

    //Check evvery position from 1 to n and assign the parrity bits

    for(int i=0;i<=n;i++){
        //Check if the position is a power of 2 or not
        if(i==1 || i==2 || i==4 || i==8 || i==16 || i==32){
            cout<<"Position : "<<i<<"Parity"<<endl;
        }
        else{
            cout<<"Position: "<<i<<"Data bit"<<endl;
        }
    }

    string hamming(n+1,'0');
    int j=0;

    for(int i=1;i<=n;i++){
        if(i==1 || i==2 || i==4 || i==8 || i==16 || i==32){
            continue;
        }
        
        hamming[i]=data[j];
        j++;
    }

    for(int i=0;i<=n;i++){
        cout<<hamming[i]<<" ";
    }

    //Calculate the parity bits

    for(int p=1;p<=n;p=p*2){
        int parity=0;

        for(int i=1;i<=n;i++){
            
            if((i&p)!=0){
                parity=parity^(hamming[i]-'0');
            }
        }
        hamming[p]=parity+'0';
    }

    cout << "Hamming code: ";

    for(int i=1; i<=n; i++){
        cout << hamming[i];
    }

    cout << endl;
    
 
    // Receiver side

    string received;

    // Take the received Hamming code
    cout << "Enter received Hamming code: ";
    cin >> received;

    // Add an extra character at index 0
    // because Hamming positions start from 1
    received = " " + received;

    // Store the error position
    int errorPosition = 0;

    // Check all parity positions
    for(int p=1; p<=n; p=p*2){

        // Store the XOR result
        int parity=0;

        // Check all positions
        for(int i=1; i<=n; i++){

            // Check whether position i belongs
            // to the parity group controlled by p
            if((i&p)!=0){

                // XOR the current bit
                parity = parity ^ (received[i]-'0');
            }
        }

        // If parity is 1, this parity check failed
        if(parity!=0){

            // Add this parity position to error position
            errorPosition = errorPosition + p;
        }
    }


    // Check whether an error was detected
    if(errorPosition==0){

        cout<<"No error detected."<<endl;
    }
    else{

        cout<<"Error detected at position: "
            <<errorPosition<<endl;

        // Correct the error by flipping the bit

        if(received[errorPosition]=='0'){
            received[errorPosition]='1';
        }
        else{
            received[errorPosition]='0';
        }

        // Display corrected Hamming code
        cout<<"Corrected Hamming code: ";

        for(int i=1;i<=n;i++){
            cout<<received[i];
        }

        cout<<endl;
    }


    // Extract the original data bits

    string recoveredData="";

    for(int i=1;i<=n;i++){

        // Non-power-of-2 positions contain data
        if(!(i==1 || i==2 || i==4 || i==8 ||
            i==16 || i==32)){

            recoveredData += received[i];
        }
    }

    // Display recovered data
    cout<<"Recovered data: "<<recoveredData<<endl;
    return 0;
    
}

