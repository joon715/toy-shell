#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <errno.h>

#define MAX_LEN_LINE    100
#define LEN_HOSTNAME	30
#define MAX_PATH	1024	

extern char **environ;

int main(void)
{
    char command[MAX_LEN_LINE];
    char arg1[MAX_LEN_LINE], arg2[MAX_LEN_LINE];
    char current_address[MAX_LEN_LINE];
    int ret, status;
    pid_t pid, cpid;
    int count = 0, i = 0, j = 0;;

    // get host name
    char hostname[LEN_HOSTNAME + 1];
    memset(hostname, 0x00, sizeof(hostname));
    gethostname(hostname, LEN_HOSTNAME);

    // get current address
    char strBuffer[MAX_PATH];
    getcwd(strBuffer, MAX_PATH);
    
    while (true) {
        char *s;
        int len, args_len;
	char **args = NULL;
	i = 0;
	j = 0;
	count = 0;

	// command-line prompt
	printf("%s","\033[35m");	//change color to green
        printf("%s@%s", getpwuid(getuid())->pw_name,hostname);
	printf("%s","\033[0m");		//change color to white
	printf(":");
	printf("%s","\033[36m");	//change color to blue
	printf("%s/", strBuffer);
	printf("Myshell");
	printf("%s","\033[0m");
	printf("$ ");

	// input command
        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        
        len = strlen(command);

	// count the number of arguments
	while(command[i] != '\n'){
		if(command[i] == ' ')
			count++;
		i++;	
	}
	args_len = count + 1;

	// set the end of command array as NULL
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
         
        printf("->Command : [%s]\n", command);
        printf("->Length of command : %d\n", len);

	// Malloc args
	args = (char **)malloc(sizeof(char *) * (args_len + 1));
	for(i = 0; i < (args_len + 1); i++){
		args[i] = (char *)malloc(sizeof(char) * 30);
	}

	count = 0;
	for(i = 0; i < len; i++){
		if(command[i] == ' '){
			args[count][j] = '\0';
			count++;
			j = 0;
		}
		else{
			args[count][j] = command[i];
			j++;
		}
	}

	// set the end of args array as "NULL"
	args[args_len] = NULL;
	
	for (i = 0; i < args_len; i++)
		printf("->arg%d : [%s]\n",i ,args[i]);

           
	printf("<<<<<Execute Command>>>>>\n");
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
	                printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
	    
	    // Use exit command to close the shell
	    if(strcmp(args[0], "exit") == 0){
		    return 0;
	    }

        }
        else {  /* child */
	    // Use exit command to colse the shell
	    if(!strcmp(args[0], "exit")){
		    printf("Myshell is closed\n");
		    return 0;
	    }

	    // Incarnate "ls" command
	    if(!strcmp(args[0], "ls")){
		    ret = execve("/usr/bin/ls", args, environ);
		    if (ret < 0) {
			fprintf(stderr, "execve failed\n");   
			return 1;
		    }
	    }

	    // Incarnate "pwd" command
	    if(!strcmp(args[0], "pwd")){
		    ret = execve("/usr/bin/pwd", args, NULL);
		    if (ret < 0) {
			fprintf(stderr, "execve failed\n");   
			return 1;
		    }
            }
	    

	    ret = execve(args[0], args, NULL);

	    if (ret < 0) {
		fprintf(stderr, "execve failed\n");   
		return 1;
		} 
	    }

	// free dynamic array
	for(i = 0; i < (args_len + 1); i++)
		free(args[i]);
	free(args);


    }

    return 0;
}
