#include <stdio.h>
 
int main()
{
    char* fileName;
    printf("Specify file name you would like to print to: \n");
    scanf("%s", fileName);
 

    FILE* file1 = fopen(fileName, "a+");
 
    char c;
    while ((c=getchar()) != EOF)
    {
    	/*Error: improper use of fprintf*/
        fprintf(file1, "%c", c);
    }
 
    fclose(file1);
 
    printf("CTRL+d is a correct ending\n");
 
    return 0;
}
