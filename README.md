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