# toy-shell

**Developed by Woojoong Kim (20153330).<br/> 
Developed in WSL2 environment.<br/> 


**"Upgrade list"<br/>


##1. I upgrade the command-line prompt showing user, host.
-> Colored the "user" purple, colored the host "blue"<br/>
-> Refered to the code from gethostusername.c that the professor gave.<br/>

##2. I upgrade the Myshell to closed by "exit" command.
-> Using string function strcmp(char *s1, char *s2) to compare args[0] and "exit" literal.<br/>
-> When Myshell is closed, it prints "Myshell is closed" message on terminal.<br/>

##3. I upgrade the command-line prompt showing "Current Working Directory".
-> Using getcwd function to get current working directory<br/>

##4. I upgrade the terminal to use simple command without command directory.
-> Upgrade the simple commands : "ls", "pwd"<br/>

##5. I upgrade the terminal can recognize multi arguments command (ls -l).
-> Using 2-dimenssion array to contain the arguments<br/>
-> Because of internal problem it only works properly once.<br/>

##6. I fix the error appeared in Upgrade 5.
