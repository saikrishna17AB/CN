#include<iostream>
using namespace std;

string crcdivision(string data,string key){
    int keylength=key.length();
    
    for(int i=0;i<=data.length()-keylength;i++){
        if(data[i]=='1'){
            //XOR when current bit is 1

            for(int j=0;j<keylength;j++){
                if(data[i+j]==key[j]){
                    data[i+j]='0';
                }
                else{
                    data[i+j]='1';
                }
            }
        }
    }
    return data.substr(data.length()-(keylength-1));
}

int main(){
    string data="1100110";
    string key="1101";
    int zeros=key.length()-1;

    string mergeddata=data;
    for(int i=0;i<zeros;i++){
        mergeddata+='0';
    }

    string remainder=crcdivision(mergeddata,key);
    
    string code=data+remainder;
    string received;

    cout<<"Transmitted data: ";
    cout<<code;
    cout<<"\nEnter receiveid data:";
    cin>>received;

    string remainderrec=crcdivision(received,key);
    bool iserror=false;
    
    for(char s:remainderrec){
        if(s=='1'){
            iserror=true;
            break;
        }
    }

    if(iserror){
        cout<<"Error encountered";
    }
    else{
        cout<<"String transmitted correctly";
    }
}