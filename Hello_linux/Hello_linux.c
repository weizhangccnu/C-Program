#include <stdio.h>
/***
 *
 *This is a C program for deliver parameter to main function
 *Main function received string
 *
 ***/
/***************************************************************************/
int main(int argc, char **argv)
{
    int i = 0;
    int parameter_one = 0;
    printf("%d\n",argc);
    parameter_one = atoi(argv[1]);          //convert string to int
    printf("%d\n",parameter_one);           //print integer number

    for(i=0;i<parameter_one;i++)            //looping print number
    {
        printf("output number:%d\n",i);
    }
    printf("Hello Linux!\n");
    return 0;
}
