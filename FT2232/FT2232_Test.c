#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <ftd2xx.h>

#define TxSector 64*1024            //achieve max data transcever speed
#define RxSector 64*1024
/*
 * @author: WeiZhang
 * @date: 2018-01-24
 * This program used to control FT2232 chip working on sync mode 
 * under Linux operating system
 */
/******************************************************************/
FILE *fpWrite;                      //define file pointer
FT_HANDLE ftHandle;
FT_STATUS ftStatus; 
FT_DEVICE_LIST_INFO_NODE *devInfo;  
DWORD numDevs;

UCHAR Mask = 0xff;
UCHAR Mode;
UCHAR LatencyTimer = 2;
DWORD EventDWord;
DWORD RxBytes;
DWORD TxBytes;
DWORD BytesWritten;
DWORD BytesReceived;
BYTE TxBuffer[TxSector];
BYTE RxBuffer[RxSector];

/******************************************************************/
//Open file for receive data
void OpenFile(void)
{
    if(NULL != (fpWrite = fopen("./rxdata.dat", "w+")))
    {
        printf("Open File Successfully!\n");    
    }
    else
    {
        printf("Cannot Open File!\n");    
 
    }
}
/******************************************************************/
// Write RxBuffer data to rxdata.dat file
void WriteFile(void)
{
    fwrite(RxBuffer, sizeof(BYTE), sizeof(RxBuffer), fpWrite);
}
/******************************************************************/
int OpenUSB(void)
{
    int i;
#if 1
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if(ftStatus == FT_OK)
    {
        printf("Number of devices is %d\n", numDevs);
    }
    if(numDevs > 0)
    {
        //allocate storage for list base one numbDevs
        devInfo = (FT_DEVICE_LIST_INFO_NODE *)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE) * numDevs);
        ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);
        if(ftStatus == FT_OK)
        {
            for(i=0; i<numDevs; i++)
            {
                printf("Dev %d\n", i);
                printf("  Flags = 0x%x\n", devInfo[i].Flags);
                printf("  Type = 0x%x\n", devInfo[i].Type);
                printf("  ID = 0x%x\n", devInfo[i].ID);
                printf("  LocId = 0x%x\n", devInfo[i].LocId);
                printf("  SerialNumber = %s\n", devInfo[i].SerialNumber);
                printf("  Description = %s\n", devInfo[i].Description);
                printf("  ftHandle = 0x%x\n", devInfo[i].ftHandle);
                
                if(devInfo[i].Flags & 0x02)
                {
                    //indicates the device  enumerated as high-speed mode
                    printf("%s------------------high-speed mode\n", devInfo[i].Description);
                }
                else
                {
                    printf("%s------------------low-speed mode\n", devInfo[i].Description);
                }
            }
        }
    }
#endif
    ftStatus = FT_OpenEx("USB <-> Serial Converter A", FT_OPEN_BY_DESCRIPTION, &ftHandle);
    if(ftStatus != FT_OK)
    {
        printf("Opening USB port failed with error %d !\n", ftStatus);
        getchar();
        return -1;
    }
    else
    {
        Mode = 0x00;                //reset mode
        ftStatus = FT_SetBitMode(ftHandle, Mask, Mode);
        //usleep(10000);
        Mode = 0x40;                //Sync FIFO mode
        ftStatus = FT_SetBitMode(ftHandle, Mask, Mode);
        if(ftStatus == FT_OK)
        {
            ftStatus = FT_SetLatencyTimer(ftHandle, LatencyTimer);
            ftStatus = FT_SetUSBParameters(ftHandle, RxSector, TxSector);        //(64K, 512B)
            //ftStatus = FT_SetUSBParameters(ftHandle, RxSector, 512);        //(64K, 512B)
            ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);
            ftStatus = FT_Purge(ftHandle, FT_PURGE_RX);
        }
        else
        {
            printf("FT_SetBitMode Failed!\n");
            FT_Close(ftHandle);
            getchar();
            return -1;
        }
        printf("Open USB <-> Serial Converter A port succeeded!\n");
        printf("Initialize USB successfully!\n");
    }
    return 1;
}   
/******************************************************************/
//FT2232 sent data to FPGA
void USB_OUT(void)
{
    ftStatus = FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);         //get FT status
    if(ftStatus == FT_OK)
    {
        ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);   //write data to FIFO
        if(ftStatus == FT_OK)
        {
            printf("Successfully Transmitted 512 Bytes!\n");            //success
        }
        else
        {
            printf("OUT Error!\n");                                     //failed
        }
    }
}
/******************************************************************/
//FPGA sent data to FT2232
void USB_IN(void)
{
    int i;
    static long int j = 0;
    ftStatus = FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
    if((ftStatus == FT_OK) && (RxBytes >= RxSector))
    {
        //ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
        ftStatus = FT_Read(ftHandle, RxBuffer, sizeof(RxBuffer), &BytesReceived);
        if(ftStatus == FT_OK)
        {
            //WriteFile();
            //printf("%d\n", sizeof(RxBuffer));
            //fwrite(RxBuffer, sizeof(BYTE), sizeof(RxBuffer), fpWrite);
            for(i=0;i<RxSector;i++)                                     //print RxBuffer content
            {
                j++;
                printf("j = %d: %d\n",j, RxBuffer[i]);
                fprintf(fpWrite, "%d\n", RxBuffer[i]);
            }
        }
        else
        {
            printf("Data Read Error!\n");
        }
    } 
}
/******************************************************************/
//main function
int main(int argc, char *argv[])
{
    int i;
    OpenFile();
    OpenUSB();
    for(i=0; i<TxSector; i++)
    {
        TxBuffer[i] = i % 256;
    }
#if 0
    for(i=0; i<TxSector; i++)
    {
        printf("%5d : %d\n",i, TxBuffer[i]);
        fprintf(fpWrite, "%d\n", TxBuffer[i]);
    }
#endif
    printf("Wait Command...\n");
    printf("Start USB OUT: Enter A\nStart USB IN: Enter B\n");
    char c = getchar();
    //char c = 'A';
    printf("%c\n",c);
    while(1)
    {
        switch(c)
        {
            case 'A':
                {
                    //printf("A\n");
                    USB_OUT();
                    break;
                }
            case 'B':
                {
                    printf("USB IN!\n");
                    USB_IN();
                    break;
                }
            default:
                    break;
        }
    }
    FT_Close(ftHandle);
    fclose(fpWrite);
    //Test code 
    for(i=0;i<3;i++)
    {
        printf("The %d OK!\n",i);
        usleep(8000);
    }
    printf("Running is over!\n");
    return 0;
}
