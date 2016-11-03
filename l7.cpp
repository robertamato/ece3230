#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>

using namespace std;

class signal{
private:
	double length;
	double max;
	double average;
	double* data;
	FILE* fp;
	void popul_array();
	void getaverage();
	void getmax();
public:
	//constructors.
	signal();
	signal(int filenum);
	signal(char* filename);
	//destuctor.
	~signal();
	void offset(double);
	void scale(double);
	void center();
	void normalize();
	void statistics();
	void sig_info();
	void save_file();
};

void signal::popul_array(){
//populate data array.
	data=(double*)malloc(sizeof(double)*length);
	for(int i=0;i<length;i++){
		fscanf(fp, "%lf", (data+i));
	}

}
void signal::sig_info(){
//display info
	cout
	<<length<<endl
	<<max<<endl
	<<average<<endl
	<<fp<<endl;
}

signal::signal(){
//empty constructor.
	fp=NULL;
	data=NULL;
	length=0;
	max=0;
	average=0;
}

signal::signal(int filenum){
//numeric constructor
	char infile[]="Raw_data_  ";

	if(filenum>=0&&filenum<10){
		sprintf(infile, "Raw_data_0%d.txt", filenum);
	}else if(filenum>=10){
		sprintf(infile, "Raw_data_%d.txt", filenum);
	}else{
		cerr<<"Invalid filename"<<endl;
	}
	cout<<"Opening file: "<<infile<<endl;
	fp=fopen(infile, "r");
	if(fp==NULL){
		cerr<<"Invalid file name"<<endl;
	}
	fscanf(fp, "%lf %lf", &length, &max);
	popul_array();
	getaverage();
	//fclose(fp);
}

signal::signal(char* filename){
//filename constructor.
	fp=fopen(filename, "r");
	cout<<"Opening "<<filename<<endl;
	if(fp==NULL){
		cerr<<"Invalid file name"<<endl;
		exit(0);
	}
	fscanf(fp,  "%lf %lf", &length, &max);
	popul_array();
	getaverage();
	//fclose(fp);
}

signal::~signal(){
//Deconstructor;
	free(data);
}

void signal::getaverage(){
//compute average of data.
	double sum=0;
	for(int i=0;i<length;i++){
		sum+=*(data+i);
	}
	average=sum/(double)length;
}

void signal::getmax(){
//set maxof array.
	double x=0;
	for(int i=0;i<length;i++){
		if(*(data+i)>x){
			x=*(data+i);
		}
	}
		max=x;

}

void signal::offset(double ofactor){
	for(int i=0;i<length;i++){
			*(data+i)=*(data+i)+ofactor;
		}
	getaverage();
	getmax();
}

void signal::scale(double sfactor){
	for(int i=0;i<length;i++){
		*(data+i)=*(data+i)*sfactor;
	}
	getaverage();
	getmax();
}

void signal::center(){
	for(int i=0;i<length;i++){
		*(data+i)=*(data+i)-average;
	}
	getaverage();
	getmax();
}

void signal::normalize(){
	for(int i=0;i<length;i++){
		*(data+i)=*(data+i)/max;
	}
	getaverage();
	getmax();
}

void signal::save_file(){
	char *x=(char*)malloc(sizeof(char)*100);
	cout<<"Name of save file: ";
	scanf("%s", x);
	cout<x;

	FILE* outfp=fopen(x, "w");
	fprintf(outfp,"%lf %lf\n", length, max);
	for(int i=0;i<length;i++){
		fprintf(outfp, "%lf\n", *(data+i));
	}
	free(x);
	fclose(outfp);
}
void menu(signal*);

struct xflags{
//*Global structure to keep track of flags
	bool n;
	bool f;
};

int main(int argc, char** argv){
		struct xflags flags={false, false};
		int fnum=0, i, filenameindex;
	for(i=1;i<argc;i++){
	cout<<i<<" "<<argv[i]<<endl;
	//Command line argument parsing
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
			case 'n':
			//File number case.
			{
				if(flags.f==true){
					cerr<<"filename already specified\n";
				}
				flags.n=true;
				cout<<"n=true\n";
				if(i+1>=argc){
					cerr<<"Error: No file number specified"<<endl
					<<"Enter valid number:"<<endl;
					cin>>fnum;
				}
				if(i+1<argc){
					fnum=atoi(argv[i+1]);
				}
				if(fnum==0){
					cerr<<"Error: No file number specified"<<endl
					<<"Enter valid number:"<<endl;
					cin>>fnum;
				}
				if(fnum==0){
					cerr<<"Error: No file number specified"<<endl;
					exit(0);
				}
				cout<<"filenumber:"<<fnum<<endl;
				//signal asignal(sel);
				i++;
				break;
			}
			case 'f':
			//filename case.
			{
				if(flags.n==true){
					cerr<<"file number already specified\n";
				}
				flags.f=true;
				cout<<"f=true\n";
				if(i+1<=argc){
					cerr<<"Error: No file name specified\n";
					break;
				}
				cout<<"filename:"<<argv[i+1]<<endl;
				filenameindex=i+1;
				cout<<filenameindex<<endl;
				i++;
				break;
			}
			default: 	
				cout<<"Arguement "<<argv[i]<<" is not a defined flag\n";
				break;
			}
		}

		else{
			cout<<"Option "<<argv[i]<<" is not valid\n";
		}
	}
	if(flags.n==false&&flags.f==false){
		cout<<("ERROR: No file flag detected\n<run> <-n> <file #>\nor <run> <-f> <filename>\n");
		
	}
	if(flags.n==true&&flags.f==true){
		char x;
		cerr<<"both a file number and a filename specified, which would you like to use?\n"
		"(f/n):";
		cin>>x;
		switch(x){
			case 'f':
			flags.n==false;
			break;
			case 'n':
			flags.f==false;
			break;
			default:
			cout<<"Invalid answer\n";
			exit(0);
		}
	}

	if(flags.n==true){
		signal signal(fnum);
		signal.sig_info();
		menu(&signal);
	}

	if(flags.f==true){
		signal signal(argv[filenameindex]);
		signal.sig_info();
		menu(&signal);
	}

	signal();
	return 1;

}

void menu(signal* signal){
	menu:
	int sel=0;
	double factor=0;
	cout<<
	"MENU :)\n"
	"{1} Offset\n{2} Scale\n{3} Center\n{4} Normalize\n{5} Statistics\n{0} Exit\n";
	cin>>sel;
	switch (sel){

		case 1:
		cout<<"By how much would you like to offset the signal?\n:";
		cin>>factor;
		cout<<endl;
		signal->offset(factor);
		signal->sig_info();
		break;

		case 2:
		cout<<"By how much would you like to scale the signal?\n:";
		cin>>factor;
		cout<<endl;
		signal->scale(factor);
		signal->sig_info();
		break;

		case 3:
		cout<<"Centering signal...\n";
		signal->center();
		signal->sig_info();
		break;

		case 4:
		cout<<"Normalizing signal...\n";
		signal->normalize();
		signal->sig_info();
		break;

		default:
		cout<<"Are you sure you want to quit? (1=y/0=n)\n";
		cin>>sel;
		if(sel==1){
			signal->save_file();
			return;
		}

	}
	goto menu;
}
