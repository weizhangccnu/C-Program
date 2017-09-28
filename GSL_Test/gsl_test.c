#include <stdio.h>
#include <unistd.h>
#include <gsl/gsl_sf_bessel.h>
/*  Bessel function test
 *  Test getopt function 
 */
int main(int argc, char **argv)
{
    int optC = 0;                   //receive arguement
    int i = 0;
    int iStop, iStart;
    i = atoi(argv[1]);
    printf("%d\n",i);
    double x = 5.0;
    while((optC = getopt(argc, argv, "e:s:")) != -1) 
    {
        switch(optC) 
        {
            case 'e':
                iStop = atoi(optarg);
                break;
            case 's':
                iStart = atoi(optarg);
                break;
            default:
                break;
         }
    }
    argc -= optind;
    argv += optind;
    printf("%d\n", iStop);
    printf("%d\n", iStart);
    double y = gsl_sf_bessel_J0(x);
    printf("J0(%g) = %.18e\n", x, y);
    return 0;
}
