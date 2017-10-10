#include <stdio.h>
#include <hdf5.h>

#define MAIN_DEGUB
#define SQRT(x) ((x) * (x))
#define STUDENT(name) student_ ## name
struct STUDENT(info)                  /* define a struct */
{
    char *name;
    int age;
};

/*This is a C program for delivering parameters to main function
 *Main function received string parameters
 *
 *@author: WeiZhang
 *@date: 2017-09-12 
 *
 */

/***************************************************************************/
int operate_struct(char *name, int age)
{
    struct STUDENT(info) *STUDENT(information);
    (*STUDENT(information)).name = "WeiZhang";
    STUDENT(information)->age = age; 
    printf("name: %s\n"
           "age : %d\n",
           STUDENT(information)->name, STUDENT(information)->age);
}
/***************************************************************************/
int sum_ab(int a, int b)
{
    int c = 0;
    c = a + b;
    printf("sum of c:\n"
           " a = %d\n"
           " b = %d\n"
           " c = %d\n",
           a, b, c);
    printf("%d\n",c);
    printf("size of size_t: %d\n",sizeof(size_t));
    printf("size of int: %d\n",sizeof(int));
    printf("size of char: %d\n",sizeof(char));
    printf("SQRT of a plus b: %d\n",SQRT(a+b));
    return 0;
}

/***************************************************************************/
/*
 * main function used to receive paramters and convert string parameters into int or other data-type
 */
#ifdef MAIN_DEGUB
int main(int argc, char **argv)
{
    int i = 0;
    int parameter_one = 0;
    //standard error output
    fprintf(stderr, "waveform_attribute:\n"
                    "chMake: %d\n"
                    "  Name: %s\n",
                    12, "WeiZhang");
    printf("%d\n",argc);
    parameter_one = atoi(argv[1]);          //convert string to int printf("%d\n",parameter_one);           //print integer number 
    for(i=0; i<parameter_one; i++)          //looping print number
    {
        printf("output number:%d\n",i);
        usleep(100000);                     //delay 100ms
    }
    printf("Hello Linux!\n");
    return 0;
}
#endif
