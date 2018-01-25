#include <stdio.h>
#include <unistd.h>
#include <ftd2xx.h>
/*
 * @author: WeiZhang
 * @date: 2018-01-24
 * This program used to control FT2232 chip working on sync mode 
 * under Linux operating system
 */
/******************************************************************/
// Get driver version
void Get_Driver_Version(FT_HANDLE ftHandle)
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
void Get_Library_Version()
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
// Purge Rx and Tx Buffer
void Purge_Buffer(FT_HANDLE ftHandle)
{
    FT_STATUS ftStatus;
    ftStatus = FT_Purge(ftHandle, FT_PURGE_RX | FT_PURGE_TX);    //Purge both Rx and Tx buufers
    if(ftStatus == FT_OK)
    {
        printf("FT_Purge succeed!\n");
    }
    else
    {
        printf("FT_Purge failed!\n");
    }
}
/******************************************************************/
// Reset FTDI device
void Reset_Device(FT_HANDLE ftHandle)
{
    FT_STATUS ftStatus;
    ftStatus = FT_ResetDevice(ftHandle);
    if(ftStatus == FT_OK)
    {
        printf("FT_ResetDevice succeed!\n");
    }
    else
    {
        printf("FT_ResetDevice failed!\n");
    }
}
/******************************************************************/
// Set device to sync fifo mode
FT_STATUS Set_Device_Mode(FT_HANDLE ftHandle, UCHAR Mode)
{
    FT_STATUS ftStatus;
    UCHAR Mask = 0xff;
    ftStatus = FT_SetBitMode(ftHandle, Mask, Mode);
    if(ftStatus == FT_OK)
    {
        printf("Config mode succeed!\n");
    }
    else
    {
        printf("Config mode failed!\n");
    }
    return ftStatus;
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
        ftStatus = FT_GetDeviceInfoDetail(0, &Flags, &Type, &ID, &LocId, SerialNumber, Description, &ftHandleTemp);
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
    ftStatus = FT_OpenEx(SerialNumber, FT_OPEN_BY_SERIAL_NUMBER , &ftHandle);     
    if(ftStatus == FT_OK)
    {
        printf("FT_Open succeed!\n");
        Get_Driver_Version(ftHandle);                       //Get driver version
        Get_Library_Version();                              //Get library version
        //Purge_Buffer(ftHandle);                           //Purge Rx and Tx Buffer
        //Reset_Device(ftHandle);                           //Reset device
        Set_Device_Mode(ftHandle, 0x00);                    //Reset mode
        usleep(1000);
        if(Set_Device_Mode(ftHandle, 0x40) == FT_OK)        //Set device to sync 245 fifo mode
        {
            ftStatus = FT_SetLatencyTimer(ftHandle, 16);    //Set latency time
            if(ftStatus == FT_OK)
            { 
               printf("right!\n");
            }
            ftStatus = FT_SetUSBParameters(ftHandle, 0x10000, 0x10000);     //set USB parameter
            if(ftStatus == FT_OK)
            { 
               printf("right!\n");
            }
            ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);  //set flow control 
            if(ftStatus == FT_OK)
            { 
               printf("right!\n");
            }
        }
    }
    else
    {
        printf("FT_Open failed!\n");
    }
    FT_Close(ftHandle);                             //close handle
    //Test code 
    for(i=0;i<3;i++)
    {
        printf("The %d OK!\n",i);
        usleep(8000);
    }
    printf("Running is over!\n");
    return 0;
}

