#include <stdio.h>

int factorial ( int num )
{
	/*
	Error: infinite recursion due to 
	incorrect factorial function
    return num * factorial( num - 1 );
	*/
	if(num>=1){
		return num*factorial(num-1);
	}
	else{
		return 1;
	}
}

int main(void)
{
    int no,ans;
    printf("Enter the number \n");
    scanf( "%d", &no );
    ans = factorial( no );
    printf("The factorial is %d\n", ans );
    return 0;
}
