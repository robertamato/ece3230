#include <stdio.h>
void main()
{
    /*
	Cannot modify string elements if declared as read only memory 
	by using pointer allocation, to allow writing use array
	to declare string

    char *p = "Mizzou";
    */

    char p[]="Mizzou";
    p[ 3 ] = 'P';
	printf("%s",p);

}
