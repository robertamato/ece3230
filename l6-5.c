#include<stdio.h>
#include<malloc.h>
void main()
{
    char *a = "hey";
   /*
	Error, free function is valid of allocated memory 
	only, declared pointer variables do not need to be
	explicitly freed
   free( a );
   */
    a = "hello";   
    printf("%s\n",a);
}
