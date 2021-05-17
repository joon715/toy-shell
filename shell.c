#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#define MAX_LEN_LINE    100
#define LEN_HOSTNAME	30

int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;

    // get host name
    char hostname[LEN_HOSTNAME + 1];
    memset(hostname, 0x00, sizeof(hostname));
    gethostname(hostname, LEN_HOSTNAME);
    
    while (true) {
        char *s;
        int len;
        
	// command-line prompt
	printf("%s","\033[35m");	//change color to green
        printf("%s@%s", getpwuid(getuid())->pw_name,hostname);
	printf("%s","\033[0m");		//change color to white
	printf(":");
	printf("%s","\033[36m");	//change color to blue
	printf("Myshell ");
	printf("%s","\033[0m");
	printf("&");

        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        
        len = strlen(command);
        printf("%d\n", len);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        
        printf("[%s]\n", command);
      
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
            ret = execve(args[0], args, NULL);

	    // Use exit command to colse the shell
	    if(strcmp(args[0], "exit") == 0){
		    printf("Myshell is closed\n");
		    return 0;
	    }

            if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
        } 
    }
    return 0;
}
