//l8.cpp
#include <iostream>
#include <cstring>
#include <string>

#define ALPHA_LEN 30

using namespace std;

//database.
char latinAlphabet[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '.', ',', '?', ' '};
char lowerLatinAlphabet[]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', ',', '?', ' '};
string morseAlphabet[]={".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".-.-.-", "--..--", "..--..", "|"};

//Base class
class Msg
{
public:
	Msg();
	Msg(string);
	~Msg();
	virtual void printInfo();
protected:
	string message;
	int length;
};

//Empty constructor
Msg::Msg(){
	cout<<"Enter a message:\n";
	getline(cin, message);
	//cin>>message;
	length=message.length();
};

//Parametric constructor.
Msg::Msg(string m){
	message=m;
	length=message.length();
}
//Destructor.
Msg::~Msg(){
}

void Msg::printInfo(){
//Base class method.
	cout<<message<<endl;
}

//Derived class
class Mcmsg: public Msg
{
public:
	Mcmsg(){
		trans_msg=new string[message.length()];
		translate();
}
	~Mcmsg(){
		delete trans_msg;
}
	void translate(){ 
	//set trans_msg to morse code equivalent.
		for(int i=0;i<message.length();i++){
			cout<<"["<<i<<"]";
			cout<<"["<<message[i]<<"]"<<endl;
			for(int j=0;j<ALPHA_LEN;j++){
				if(message[i]==latinAlphabet[j]||message[i]==lowerLatinAlphabet[j]){
					cout<<"["<<j+1<<"]";
					cout<<morseAlphabet[j]<<endl;
					trans_msg[i]=morseAlphabet[j];
				}
			}
		} 
	}

	void printInfo(){
	//Derived class method.
		cout<<message<<endl;
		for(int i=0;i<message.length();i++){
			cout<<*(trans_msg+i);
		}
		cout<<endl;
	}
private:
	string* trans_msg;
};


class MsgStack
{
public:
	MsgStack(){
		next=NULL;
	}
	~MsgStack(){
		delete this;
	}
	MsgStack* push(MsgStack* x){
		x->next=this;
		return x;
	}
	void pop(){

	} //pop implemented in print stack funtion
	void printStack(MsgStack* x){
		while(x!=NULL){
			//pop function
			x->msg.printInfo();
			x=x->next;
		}
	}

private:
	Mcmsg msg;
	MsgStack* next;
};

int main(){
	char sel;

	//set head of link list.
	MsgStack* head=new MsgStack;
		
	while(1){
	//populate link list stack.
		cout<<"Enter another message? y,n: ";
		cin>>sel;
		if(sel!='y'){
			break;
		}
			cin.ignore();
			MsgStack* temp=new MsgStack;
			head=head->push(temp);
	}
		cout<<endl;
		head->printStack(head);
}
