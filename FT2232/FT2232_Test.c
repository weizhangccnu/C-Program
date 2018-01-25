#include <stdio.h>
#include <unistd.h>
#include <ftd2xx.h>
/*
 * @author: WeiZhang
 * @date: 2018-01-24
 * This program used to control FT2232 chip working under Async mode 
 * under Linux operating system
 */
/******************************************************************/
// Get driver version
void Get_driver_version(FT_HANDLE ftHandle)
{
    FT_STATUS ftStatus;
    DWORD dwDriverVer;
    ftStatus = FT_GetDriverVersion(ftHandle, &dwDriverVer);
    if(ftStatus == FT_OK)
    {
        printf("Driver version = 0x%x\n", dwDriverVer); 
    }
    else
    {
        printf("error reading driver version\n");
    }
}
/******************************************************************/
// Get library version
void Get_library_version()
{
    FT_STATUS ftStatus;
    DWORD dwLibraryVer;
    ftStatus = FT_GetLibraryVersion(&dwLibraryVer);
    if(ftStatus == FT_OK)
    {
        printf("Library version = 0x%x\n", dwLibraryVer);
    }
    else
    {
        printf("error reading library version\n");
    }
}
/******************************************************************/
//main function
int main()
{
    int i = 0;
    FT_HANDLE ftHandle;                 //define a ft2232 hanele
    FT_STATUS ftStatus;
    FT_HANDLE ftHandleTemp;
    DWORD numDevs;
    DWORD Flags;
    DWORD ID;
    DWORD Type;
    DWORD LocId;
    char SerialNumber[16];
    char Description[64];
    //
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if(ftStatus == FT_OK)
    { 
       printf("Number of devices is %d\n",numDevs);
    } 
    else
    { 
       printf("FT_CreateDeviceInfoList failed!\n");
    } 
    if(numDevs > 0)
    {
        // get information for device 0
        ftStatus = FT_GetDeviceInfoDetail(0, &Flags, &Type, &ID, \
        &LocId, SerialNumber, Description, &ftHandleTemp);
        if(ftStatus == FT_OK)
        {
            printf("Dev 0:\n");
            printf(" Flag=0x%x\n", Flags);
            printf(" Type=0x%x\n", Type);
            printf(" ID  =0x%x\n", ID);
            printf(" LocId=0x%x\n", LocId);
            printf(" SerialNumber=%s\n", SerialNumber);
            printf(" Description=%s\n", Description);
            printf(" ftHandle=0x%x\n", ftHandleTemp);
        }
    }
    //Opne ftdi device 
    ftStatus = FT_OpenEx(SerialNumber, FT_OPEN_BY_SERIAL_NUMBER , &ftHandle);   //Open ftdi device
    if(ftStatus == FT_OK)
    {
        printf("FT_Open succeed!\n");
        Get_driver_version(ftHandle);
        Get_library_version();
    }
    else
    {
        printf("FT_Open failed!\n");
    }

    //close handle
    FT_Close(ftHandle);

    //Test code 
    for(i=0;i<3;i++)
    {
        printf("The %d OK!\n",i);
        usleep(8000);
    }
    printf("Running is over!\n");
    return 0;
}

