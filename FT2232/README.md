## Control FT2232H chip on the 245 sync FIFO mode ##
### 1. This program run under Linux operating system ###
  - [Linux lib file link](http://www.ftdichip.com/Drivers/D2XX.htm)
  - [FT2232H datasheet](http://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT2232D.pdf)
### 2. Linux lib installation steps ###
  - installation .h file on release directory
```
sudo cp ftd2xxx.h /usr/local/include
sudo cp WinTypes.h /usr/local/include
```
  - installation share object (.so) file on build directory
```
sudo cp libftd2xxx.* /usr/local/lib
sudo chmod 0755 /usr/local/lib/libftd2xx.so.1.4.6
sudo ln -sf /usr/local/lib/libftd2xx.so.1.4.6 /usr/local/lib/libftd2xx.so
```
### 3. Software application development ###
  - [D2XX programmer's guide](http://www.ftdichip.com/Support/Documents/ProgramGuides/D2XX_Programmer's_Guide(FT_000071).pdf)
### 4. Software application development ###
  - The exectuable file (FT2232_Test) should run with root privilage on Linux operating system
```
sudo ./FT2232_Test
```
### 5. Remove module "ftdi_sio"
```
sudo rmmod ftdi_sio
```
