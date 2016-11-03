/*----------------------------------------------/
/ Robert Amato									/
/ Ece 3230										/
/ Sept 29, 2016									/
/ Lab 5, update lab4 with command line flags	/
/----------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

//*Global structure to keep track of flags
struct xflags{
	bool n;
	bool o;
	bool s;
	bool S;
	bool C;
	bool N;
	bool r;
	bool h;
};

void printa(int* , int);
void printb(double* , int);
double get_mean(int* , int);
int get_max(int* , int);
int output_data(char*, int, double, double*);
void printhelp();

int main(int argc,char* argv[]){
	struct xflags flags={false, false, false, false, false, false, false, false};
	int sel, size, max, i, *a, nsindex;
	double ofactor, sfactor, mean;
	char str[100];

//Command line argument parsing
	for(i=1;i<argc;i++){
		if(argv[i][0]=='-'){
			switch(argv[i][1]){
			case 'n':
				flags.n=true;
				if(i+1>=argc){
					printf("Error: No file number specified\n");
					exit(0);
				}
				sel=atoi(argv[i+1]);
				if(sel==0){
					printf("Error: File number does not follow -n flag\n");
					exit(0);
				}
				i++;
				break;
			case 'o':
				flags.o=true;
				if(i+1>=argc){
					printf("Error: No offset factor specified\n");
					exit(0);
				}
				ofactor=atoi(argv[i+1]);
				if(ofactor==0){
					printf("Error: Offset factor does not follow -o flag\n");
					exit(0);
				}
				i++;
				break;
			case 's':
				flags.s=true;
				if(i+1>=argc){
					printf("Error: no scale factor specified\n");
					exit(0);
				}
				sfactor=atoi(argv[i+1]);
				if(sfactor==0){
					printf("Error: Scale factor does not follow -s flag\n");
					exit(0);
				}
				i++;
				break;
			case 'S':
				flags.S=true;
				break;
			case 'C':
				flags.C=true;
				break;
			case 'N':
				flags.N=true;
				break;
			case 'r':
				flags.r=true;
				nsindex=i+1;
				i++;
				break;
			case 'h':
				flags.h=true;
				break;
			default: 	
				printf("Arguement %s is not a defined flag\n", argv[i]);
				break;
			}
		}

		else{
			printf("Option %s is not valid\n", argv[i]);
		}
	}
	if(flags.h==true){
				printhelp();
	}
	
	if(flags.n==false){
		printf("ERROR: No file flag detected\n<run> <-n> <file #>\n");
		exit(0);

	}
//keep name convention by appending leading 0
	if(sel<10){
		sprintf(str, "Raw_data_0%d.txt", sel);
	}
	else{
		sprintf(str, "Raw_data_%d.txt", sel);
	}
	printf("Opening file: %s\n", str);

//Populate input array 'a'
	FILE* fp=fopen(str, "r");
	if(fp==NULL){
		printf("Error: unable to open file %s\n", str);
		exit(0);
	}
	fscanf(fp, "%d %d", &size, &max);
	a=malloc(sizeof(int)*size);
	for(i=0;i<size;i++){
		fscanf(fp, "%d", (a+i));
	}
	fclose(fp);
	if(flags.r==true){
		printf("Copying %s ", str);
		sprintf(str, "%s.txt", argv[nsindex]);
		printf("to %s\n", str);
		fp=fopen( argv[nsindex],"w");	
	}
	printf("DATA->\n");
	printa(a, size);
	mean=get_mean(a, size);
	max=get_max(a, size);
	printf("Average of input file is %lf\n", mean);
	printf("Max value of input file is %d\n", max);

	//Malloc space for reusable output array
	double* b=malloc(sizeof(double)*size);

	//Offset
	if(flags.o==true){
		for(i=0;i<size;i++){
			*(b+i)=(double)*(a+i)+ofactor;
		}	
		if(flags.r==true){
			sprintf(str, "%s_Offset.txt", argv[nsindex]);
		}
		else{
			if(sel<10){
				sprintf(str, "Offset_data_0%d.txt", sel);
			}
			else{
				sprintf(str, "Offset_data_%d.txt", sel);
			}
		}	
		printf("Outputing to file %s ...\n", str);
		if(output_data(str, size, ofactor, b)==0){
			printf("Error: unable to open output file %s\n", str);
		}
		printb(b, size);
	}

	//Scaling
	if(flags.s==true){
		for(i=0;i<size;i++){
			*(b+i)=(double)*(a+i)*sfactor;
		};
		if(flags.r==true){
			sprintf(str, "%s_Scale.txt", argv[nsindex]);
		}
		else{
			if(sel<10){
				sprintf(str, "Scale_data_0%d.txt", sel);
			}
			else{
				sprintf(str, "Scale_data_%d.txt", sel);
			}
		}
		printf("Outputing to file %s ...\n", str);
		if(output_data(str, size, sfactor, b)==0){
			printf("Error: unable to open file %s\n", str);
		}
		printb(b, size);
	}
	

//Part 2.3 Statistics Data
	if(flags.S==true){
		if(flags.r==true){
			sprintf(str, "%s_Offset.txt", argv[nsindex]);
		}
		else{
			if(sel<10){
				sprintf(str, "Statistics_data_0%d.txt", sel);
			}
			else{
				sprintf(str, "Statistics_data_%d.txt", sel);
			}
		}
		printf("Outputing to file %s ...\n", str);
		fp=fopen(str, "w");
		fprintf(fp, "%lf %d\n",get_mean(a, size), get_max(a, size));
		fclose(fp);
	}

//Part 2.4, Center Data
	if(flags.C==true){
		if(flags.r==true){
			sprintf(str, "%s_Offset.txt", argv[nsindex]);
		}
		else{
			if(sel<10){
				sprintf(str, "Centered_data_0%d.txt", sel);
			}
			else{
				sprintf(str, "Centered_data_%d.txt", sel);
			}
		}
		printf("Outputing to file %s ...\n", str);
		fp=fopen(str, "w");
		fprintf(fp, "%d -%lf\n", size, mean);
		for(i=0;i<size;i++){
			*(b+i)=(double)*(a+i)-mean;
			fprintf(fp, "%lf\n", *(b+i));
		}
		fclose(fp);
	}

//Part 2.5, Normalize Data
	if(flags.N==true){
		if(flags.r==true){
			sprintf(str, "%s_Offset.txt", argv[nsindex]);
		}
		else{
			if(sel<10){
				sprintf(str, "Normalized_data_0%d.txt", sel);
			}
			else{
				sprintf(str, "Normalized_data_%d.txt", sel);	
			}
		}
		printf("Outputing to file %s ...\n", str);
		fp=fopen(str, "w");
		fprintf(fp, "%d %d\n", size, max);	
		for(i=0;i<size;i++){
			*(b+i)=(double)*(a+i)/max;
			fprintf(fp, "%lf\n", *(b+i));
		}
		fclose(fp);

		free(a);
		free(b);
	}
}

void printa(int* a, int size){
//prints integer array
	int i;
	puts(" ");
	for(i=0;i<size;i++){
		printf("%d\n", *(a+i));
	}
}

void printb(double* b, int size){
//prints reuseable double array 
	int i;
	puts(" ");
	for(i=0;i<size;i++){
		printf("%lf\n", *(b+i));
	}
}

double get_mean(int* a, int size){
//gets mean of int array
	int i, sum=0;
	double mean;
	for(i=0;i<size;i++){
		sum+=*(a+i);
	}
	mean=(double)sum/size;
	return mean;
}

int get_max(int* a, int size){
//get max of int array
	int i, max=0;
	for(i=0;i<size;i++){
		if(max<*(a+i)){
			max=*(a+i);
		}
	}
	return max;
}

int output_data(char* str, int size, double factor, double* b){
	int i;
	FILE* fp=fopen(str, "w");
	if(fp==NULL){
		return 0;
	}
	fprintf(fp, "%d %lf\n", size, factor);
	for(i=0;i<size;i++){
		fprintf(fp, "%lf\n", *(b+i));
	}
	fclose(fp);
	return 1;
}

void printhelp(){
	printf("HELP PAGE :)\n");
	printf("To open a file, use -n flag followed by the file number\n EX: -n 3\n");
	printf("Flags:\n");
	printf("-n: File number (value needed)\n");
	printf("-o: offset value (value needed)\n");
	printf("-s: scale factor (value needed)\n");
	printf("-S: Get statistics\n");
	printf("-C: Center the signal\n");
	printf("-N: Normalize signal\n");
	printf("-r: Rename files (name needed)\n");
	printf("-h: Help (display how the program should be called, including the different input options)\n\n");
	return;
}