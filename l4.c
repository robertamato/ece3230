/*----------------------------------------------/
/ Robert Amato									/
/ Ece 3230										/
/ Sept 29, 2016									/
/ Lab 4, functions, arrays, and file handling	/
/----------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"

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

int main(){
	int sel, sel2, os, size, max, i, *a;
	double factor, mean;
	char str[100];
	printf("What file would you like to open?\n");
	scanf("%d", &sel);
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
	printa(a, size);
	mean=get_mean(a, size);
	max=get_max(a, size);
	printf("Average of input file is %lf\n", mean);
	printf("Max value of input file is %d\n", max);

//switch to perform either offset or scaling function
	printf("Would you like to {1} offset or {2} scale original signal?\n");
	scanf("%d", &os);
	//Malloc space for reusable output array
	double* b=malloc(sizeof(double)*size);

	switch (os){
	//Offset
	case 1:
		printf("By how much would you like to offset the array?\n");
		scanf("%lf", &factor);
		for(i=0;i<size;i++){
		*(b+i)=(double)*(a+i)+factor;
		}
		if(sel<10){
			sprintf(str, "Offset_data_0%d.txt", sel);
		}
		else{
			sprintf(str, "Offset_data_%d.txt", sel);
		}
		break;

	case 2:
	//Scaling
		printf("By how much would you like to scale the array?\n");
		scanf("%lf", &factor);
		for(i=0;i<size;i++){
			*(b+i)=(double)*(a+i)*factor;
		};
		if(sel<10){
			sprintf(str, "Scale_data_0%d.txt", sel);
		}
		else{
			sprintf(str, "Scale_data_%d.txt", sel);
		}
		break;

	default:
		printf("Invalid selection\n");
		exit(0);
	}

	printb(b, size);

//Output to file
	fp=fopen(str, "w");
	if(fp==NULL){
		printf("Error: unable to open file\n");
		exit(0);
	}
	fprintf(fp, "%d %lf\n", size, factor);
	for(i=0;i<size;i++){
		fprintf(fp, "%lf\n", *(b+i));
	}
	fclose(fp);

//Part 2.3 Statistics Data
//Output Statistics Data
	if(sel<10){
		sprintf(str, "Statistics_data_0%d.txt", sel);
	}
	else{
		sprintf(str, "Statistics_data_%d.txt", sel);
	}
	fp=fopen(str, "w");
	fprintf(fp, "%lf %d\n",get_mean(a, size), get_max(a, size));
	fclose(fp);

//Part 2.4, Center Data
//set mean to 0 by subtracting mean from all elements
	if(sel<10){
		sprintf(str, "Centered_data_0%d.txt", sel);
	}
	else{
		sprintf(str, "Centered_data_%d.txt", sel);
	}
	fp=fopen(str, "w");
	fprintf(fp, "%d -%lf\n", size, mean);
	for(i=0;i<size;i++){
		*(b+i)=(double)*(a+i)-mean;
		fprintf(fp, "%lf\n", *(b+i));
	}
	fclose(fp);

//Part 2.5, Normalize Data
//set values to between [0, 1] by dividing by max
	if(sel<10){
		sprintf(str, "Normalized_data_0%d.txt", sel);
	}
	else{
		sprintf(str, "Normalized_data_%d.txt", sel);	
	}
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