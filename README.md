# toy-shell

Dveloped by Woojoong Kim (20153330)
Developed in WSL2 environment


<Upgrade list>
1. I upgrade the command-line prompt showing user, host.
-> Colored the "user" green, colored the host "blue"
-> Refered to the code from gethostusername.c that the professor gave.

2. I upgrade the Myshell to closed by "exit" command
-> Using string function strcmp(char *s1, char *s2) to compare args[0] and "exit" literal.
-> When Myshell is closed, it prints "Myshell is closed" message on terminal.

3. I upgrade the command-line prompt showing "Current Working Directory"
-> Using getcwd function to get current working directory

4. I upgrade the terminal to use simple command without command directory
-> Upgrade the simple commands : "ls", "pwd"
