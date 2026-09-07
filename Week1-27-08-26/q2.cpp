#include<iostream>
using namespace std;

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

string bytestuffing2(string inp){
	string output="";
	for(int i=0;i<inp.length();i++){
		if(inp[i]=='F' && (i!=0 && i!=inp.length()-1)){
			output+='E';		
		}
		if(inp[i]=='E'){
			output+='E';	
		}	
		output+=inp[i];
	}	
	return output;
} 

string bytedestuffing2(string inp){
	string output="";
	for(int i=0;i<inp.length();i++){
		if(inp[i]=='E'){
			output+=inp[i+1];
			i++;
		}
		else{
			output+=inp[i];		
		}
	}
	return output;
}




int main(){

	// string i="FABCDEFFEDFF";
	
	cout<<"Enter string";
	string i;
	cin>>i;
	cout<<"\n";
	string o=bytestuffing2(i);
	cout<<o;
	cout<<"\n";
	cout<<bytedestuffing2(o);
	return 0;

}