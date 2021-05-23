# toy-shell

Developed by Woojoong Kim (20153330)\n
Developed in WSL2 environment\n


"Upgrade list"
1. I upgrade the command-line prompt showing user, host.\n
-> Colored the "user" purple, colored the host "blue"\n
-> Refered to the code from gethostusername.c that the professor gave.\n

2. I upgrade the Myshell to closed by "exit" command\n
-> Using string function strcmp(char *s1, char *s2) to compare args[0] and "exit" literal.\n
-> When Myshell is closed, it prints "Myshell is closed" message on terminal.\n

3. I upgrade the command-line prompt showing "Current Working Directory".\n
-> Using getcwd function to get current working directory\n

4. I upgrade the terminal to use simple command without command directory.\n
-> Upgrade the simple commands : "ls", "pwd"\n

5. I upgrade the terminal can recognize multi arguments command (ls -l).\n
-> Using 2-dimenssion array to contain the arguments\n
-> Because of internal problem it only works properly once.\n

6. I fix the error appeared in Upgrade 5.\n
