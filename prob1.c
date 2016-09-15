#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.141593


float rad;
float area;
void main(){
	printf("Enter the radius of the circle in cm:\n");
	scanf("%f", &rad);
	area=pi*rad*rad;
	printf("The area of the circle is %f cm \n", area);
};
