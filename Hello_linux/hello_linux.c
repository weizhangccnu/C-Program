#include <stdio.h>
#include <hdf5.h>
#include <gsl/gsl_histogram.h>

#define MAIN_DEGUB
#define SQRT(x) ((x) * (x))
#define STUDENT(name) student_ ## name
/*This is a C program for delivering parameters to main function
 *Main function received string parameters
 *
 *@author: WeiZhang
 *@date: 2017-09-12 
 */
struct STUDENT(info)                  /* define a struct */
{
    char *name;
    int age;
};

/***************************************************************************/
/*This function is used to create a one dimension histogram
 */
int test_gsl_histogram(float a, float b, size_t n)
{
    int i;
    double dat[20] = {1, 15, 25, 23, 45, 48, 55, 56, 62, 65, 68, 70, 75, 80, 85, 90, 92, 98, 99};
    //fp = fopen("output_file.dat", 'w');
    //if (fp == NULL)
    //{
    //    printf("open file error!!\n");
    //    exit(-1);
    //}
    //fputc('a', fp);
    //fclose(fp);
    gsl_histogram *h = gsl_histogram_alloc(n);          //allocates memory for histogram struct
    gsl_histogram_set_ranges_uniform(h, a, b);          //sets the ranges of the existing histogram
    for(i = 0; i < 20; i++) 
    {
        gsl_histogram_increment(h, dat[i]);             //adds one to the bin whose range
    }
    gsl_histogram_fprintf(stdout, h, "%g", "%g");           //writes the ranges and bins of the histogram
    gsl_histogram_free(h);                              //frees the histogram pointer and all of the memory
    return 0;
}
/***************************************************************************/
int operate_struct(char *name, int age)
{
    struct STUDENT(info) *STUDENT(information);
    (*STUDENT(information)).name = "WeiZhang";
    STUDENT(information)->age = age; 
    printf("name: %s\n"
           "age : %d\n",
           STUDENT(information)->name, STUDENT(information)->age);
    return 1;
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
    //FILE *fp;
    double a, b;
    size_t n;
    int i = 0;
    int parameter_one = 0;
    //if((fp = fopen("output_file.dat", 'w')) == NULL)
    //{
    //    printf("open file error!!\n");
    //    exit(-1);
    //}
    //fputc('a', fp);
    //fclose(fp);
    if(argc != 5)
    {
        printf("Usage: gsl_histogram xmin xmax n\n"
               "Computes a histogram of the data "
               "on stdin using n bins from xmin to xmax\n");
        exit(0);
    }
    a = atof(argv[2]);
    b = atof(argv[3]);
    n = atoi(argv[4]);
    //standard error output
    fprintf(stderr, "waveform_attribute:\n"
                    "chMake: %d\n"
                    "Name  : %s\n",
                    12, "WeiZhang");
    printf("%d\n",argc);
    parameter_one = atoi(argv[1]);          //convert string to int printf("%d\n",parameter_one);
    //print integer number 
    for(i=0; i<parameter_one; i++)          //looping print number
    {
        printf("output number:%d\n",i);
        usleep(100000);                     //delay 100ms
    }
    test_gsl_histogram(a, b, n);        //test gsl_histogram function
    printf("Hello Linux!\n");
    return 0;
}
#endif
