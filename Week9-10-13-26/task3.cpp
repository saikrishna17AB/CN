#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ForwardTable{
    int no;
    string subnetaddress;
    string subnetmask;
    string firsthost;
    string lasthost;
    string broadcastaddress;
    int nhost;
}

string makeIP(int ip[]){
    return to_string(ip[0])+"."+to_string(ip[1])+"."+to_string(ip[2])+"."+to_string(ip[3]);

}


int main(){
    int ip[4],int cidr, int nsubnets;
    cout<<"Enter the IP address: ";
    cin>>ip[0]>>'.'>>ip[1]>>'.'>>ip[2]>>'.'>>ip[3];
    cout<<"\nEnter CIDR:";
    cin>>cidr;
    cout<<"\nEnter no of subnets: ";
    cin>>nsubnets;

    if (cidr < 0 || cidr > 30 || requiredSubnets <= 0){
        cout<<"Invalid input";
        return 0;
    }

    for(int i=0;i<4;i++){
        if(ip[i]<0 || ip[i]>255){
            cout<<"Invalid IP";
            return 0;
        }
    }

    int borrowed=0;
    int subnets=1;

    //Calculate the number of bits required to satisy subnets

    while(subnets<nsubnets){
        subnets=subnets*2;
        borrowed++;
    }

    int newcidr=cidr+borrowed;

    int hostbits=32-newcidr;
    int subnetsize=1;
    for(int i=0;i<hostbits;i++){
        subnetsize*=2;
    }

    int nhosts=subnetsize-2;

    int originalmask[4]={0,0,0,0};
    for(int i=0;i<cidr;i++){
        originalmask[i/8]+=1<<(7-i % 8);

    }

    int mask[4]={0,0,0,0};
    for(int i=0;i<newcidr;i++){
        mask[i%8]+= 1<<(7-1 % 8);
    }

    //Finding the network address: Put all the bits in hid to zero
    int networkid[4]={0,0,0,0};
    for(int i=0;i<4;i++){
        if(mask[i]==255){
            ;
        }
        else{
            network[i]=
        }
    }

    



}