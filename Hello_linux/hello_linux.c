#include <stdio.h>
#include <hdf5.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_histogram2d.h>

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
/*This function is used to test the one dimension histogram library
 */
int test_gsl_histogram(float a, float b, size_t n)
{
    FILE *fp;
    int i;
    double dat[20] = {32, 15, 25, 23, 45, 48, 55, 56, 62, 65, 68, 70, 75, 80, 85, 90, 92, 98, 99};
    fp = fopen("histogram_output.dat", "w");            //file acessing method should be bracketed with ""
    if (fp == NULL)
    {
        printf("open file error!!\n");
        exit(-1);
    }
    //fputc('a', fp);
    gsl_histogram *h = gsl_histogram_alloc(n);          //allocates memory for histogram struct
    gsl_histogram_set_ranges_uniform(h, a, b);          //sets the ranges of the existing histogram
    for(i = 0; i < 20; i++) 
    {
        gsl_histogram_increment(h, dat[i]);             //adds one to the bin whose range
    }
    printf("Sum of all bin values: %g\n", gsl_histogram_sum(h));
    gsl_histogram_fprintf(fp, h, "%g", "%g");           //writes the ranges and bins of the histogram
    gsl_histogram_free(h);                              //frees the histogram pointer and all of the memory
    fclose(fp);
    return 0;
}
/***************************************************************************/
/*This function is used to test the two dimension histogram library
 */
int test_gsl_histogram2d()
{
    FILE *fp;
    const gsl_rng_type *T;                              //random number generator static information   
    gsl_rng *r;                                         //define an instance of a generator 
    fp = fopen("histogram2d_output.dat", "w");          //file acessing method should be bracketed with ""
    if (fp == NULL)
    {
        printf("open file error!!\n");
        exit(-1);
    }
    gsl_histogram2d  *h = gsl_histogram2d_alloc(10, 10);//allocates memory for histogram2d struct
    gsl_histogram2d_set_ranges_uniform(h,               //sets the ranges of the existing histogram
                                       0.0, 1.0,        
                                       0.0, 1.0);
    gsl_histogram2d_accumulate(h, 0.3, 0.3, 1);         //adding one (1.0) to the bin
    gsl_histogram2d_accumulate(h, 0.8, 0.1, 5);
    gsl_histogram2d_accumulate(h, 0.7, 0.9, 0.5);

    gsl_rng_env_setup();                                //reads the environment variables
    T = gsl_rng_default;                                
    r = gsl_rng_alloc(T);

    gsl_histogram2d_fprintf(fp, h, "%g", "%g");         //writes the ranges and bins of the histogram h line-by-line to the stream
    gsl_histogram2d_free(h);                            //frees the histogram pointer and all of the memory
    gsl_rng_free(r);                                    //frees random number pointer
    fclose(fp);                                         //close file pointer
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
    double a, b;
    size_t n;
    int i = 0;
    int parameter_one = 0;
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
    test_gsl_histogram(a, b, n);            //test gsl_histogram function
    test_gsl_histogram2d();                 //test gsl_histogram2d function
    printf("Hello Linux!\n");
    return 0;
}
#endif
