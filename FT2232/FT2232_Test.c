#include <stdio.h>
#include <unistd.h>
/*
 * @author: WeiZhang
 * @date: 2018-01-24
 * This program used to control FT2232 chip working under Async mode
 */
/******************************************************************/
//main function
int main()
{
    int i = 0;
    for(i=0;i<100;i++)
    {
        printf("The %d OK!\n",i);
        usleep(8000);
    }
}
