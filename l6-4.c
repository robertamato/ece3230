 
#include <stdio.h>
#include <string.h>
void main()
{
    int i=0;
    /*
	Error, copying string of size 20 into array of size 15, increase size of array
    char arr1[ 15 ] = "Trumantiger";
    */
    char arr1[20]="Trumantiger";
    char arr2[ 20 ];
    while(i<20){
        arr2[ i ] = 'A';
	++i;
    }
    strcpy( arr1 , arr2 );
    printf("%s",arr1);
}
