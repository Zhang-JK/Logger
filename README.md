# Logger: Processing UART data from robot
## Data Format
0. Common  
   & -> starting  
   \n -> ending  
   \- -> header ending  
   \<Level>: 1 Error; 2 Warning; 3 Note; 4 Info;
   
1. Message  
```&M<Level>-<Msg>\n```  
2. State  
```&S<Level>-<name>.<value>:<name>.<value>...\n```
   
## Set Up Environment
Run the following lines to config on Linux:
```
#install compilers
sudo apt-get install build-essential
#install qt libs
sudo apt-get install qtbase5-dev
sudo apt-get install qtdeclarative5-dev
sudo apt-get install libqt5serialport5-dev
#enable serial port authority
sudo usermod -aG dialout <your-user-name>
```
Run the following lines to compile and run the program
```
mkdir ./build
cmake ./build/ .
make
./Logger
```

## For Non-GUI Version
Edit ```main.h```, comment the line ```#define USE_GUI``` and re-compile the program

## Log Info
Logs will be stored in the ```log``` folder.
Each log file is named by its start time

## TODO List
- [ ] add file reading and reviewing  
- [ ] add graph for state log  
- [ ] auto detect gui interface  
