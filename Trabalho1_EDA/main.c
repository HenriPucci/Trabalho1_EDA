#include<stdio.h>
#include<stdlib.h>

// C program for implementation of Bubble sort





int main()
{
    FILE *fp;
    char ch;
    fp = fopen("Data.csv", "r");
    
    while(1){
        ch = getc(fp);
        if(ch==EOF)
            break;
        printf("%c", ch);
    }
    fclose(fp);
    

    return 0;


}