#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long factorial(unsigned short a){
	unsigned long b=1;
	int i;
	while(a!=0){
		b=b*a;
		a-=1;
	};
	return b;
};

int main(){
	int sel, div1, div2;
	unsigned short fa;
	unsigned int year;
	float x,y;
 	top:
	printf("Menu...\n{1} Factorial of a number\n{2} Leap year or not\n{3} Maximum\n{4} Division of two numbers\n{5} Exit\n~");
	scanf("%d", &sel);
	switch (sel){
		case 1 :
			printf("Enter an integer:");
			scanf("%hu", &fa);
			if(fa>65){
				printf("\nError result will be too large to fit in an unsigned long on a 64 bit machine\n");
			break;
			}
			printf("\n%lu\n", factorial(fa));
			break;
		case 2:
			printf("Enter a year:\n");
			scanf("%i", &year);
			if(year%4==0){
				printf("year is a leap year :)\n");
			}
			else{
				printf("not a leap year :(\n");
			}
			break;
		case 3:
			printf("Enter 2 float numbers\n");
			scanf("%f", &x);
			scanf("%f", &y);
			printf("The larger number is %f\n", x>y?x:y);
			break;
		case 4:
			printf("Enter 2 integers\n");
			scanf("%d", &div1);
			scanf("%d", &div2);
			if(div2==0){
				puts("Error: Cannot divide by 0");
				break;
			}
			printf("result is %f\n", (float)div1/(float)div2);
			break;
		case 5:
			exit(1);
			break;
	};
	goto top;
};
