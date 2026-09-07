#include<iostream>
using namespace std;

bool pattern(string a,int i){
	for(int j=i;j>=i-5;j--){
		if(a[j]=='0')
			return false;
	}
	return true;
}
string bitstuffing(string imsg){
	int count=0;
	string output="";
	int j=0;
	bool con=false;	
	for(int i=0;i<imsg.length();i++){
		output+=imsg[i];	
		if(imsg[i]=='1'){
			
			count++;
			if(count==5){
				j=j+1;
				output+='0';
		 		count=0;
			}			
		}
		else{
			count=0;
		}		
		
		
	}
	return output;
}

bool destuffing(string a,int i){
	if(i-5<0)
		return false;
	for(int j=i-5;j<i;j++){
		if(a[j]=='0'){
			return false;
		}
	}
	return true;

}

string bitdestuffing(string stuf){
	string output="";
	int count=0;
	for(int i=0;i<stuf.length();i++){
		if(stuf[i]=='0' && destuffing(stuf,i)){
			continue;
		}
		output+=stuf[i];
	}
	return output;


}

string bytestuffing1(string inp){
	string output="";
	for(int i=0;i<inp.length();i++){
		if(inp[i]=='F' && (i!=0 && i!=inp.length()-1)){
			output+='E';		
		}	
		output+=inp[i];
	}
	return output;
}

string bytedestuffing2(string inp){
	
} 




int main(){
	// string input="0110101111111011010";
	string input;
	cout<<"Enter input: ";
	cin>>input;
	// cout<<input;
	cout<<"\n";
	string o=bitstuffing(input);
	cout<<o;
	cout<<"\n";
	string f=bitdestuffing(o);
	cout<<f;


//	string i="FABCDEFFEDFF";
//	cout<<i;
//	cout<<"\n";
//	cout<<bytestuffing1(i);
	return 0;

}