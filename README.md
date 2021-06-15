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
cmake .
make
./Logger
```
