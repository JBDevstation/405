#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char **argv) {
    int hflg = 0;
    int fflg = 0;
    int c = 0;
    bool hasPID = false;
    FILE *file;
    int targetPID;

    for( ; argc>1; argc--,argv++) {
        c++;
        switch(argv[1][1]) {
        case 'h':
            printf("Hello World\n");
            continue;
        case 'f':
            continue;
	default:
	    //Search for a '.', denoting if it's a txt or a PID
	    if(strchr(argv[1], '.') != NULL){
	    	//"." found, denoting that it's a .txt
            	printf("Opening : %s\n", argv[1]);
	    	file = fopen(argv[1], "r");
	    	if(file != NULL){
	    	    char c = fgetc(file);
		    while (c != EOF){
		    	printf("%c", c);
		    	c = fgetc(file);
	 	}
		fclose(file);
	    	}else{
	    		printf("File %s cannot be opened\n", argv[1]);
			exit(1);
	    	}
	    }else{
	    	printf("my_kill pid: %s\n", argv[1]);
		targetPID = atoi(argv[1]);
		hasPID = true;
	    }
	    continue;
        }
        break;
    }

    if(!hasPID){
	    printf("Error - command format is $my_kill pid\n");
	    exit(-1);
    }

    int status = kill(targetPID, SIGINT);
    int errnum = errno;
    if (status == -1){
    	fprintf(stderr, "Value of errno: %d\n", errno);
    	perror("Error printed by perror");
	fprintf(stderr, "Error killing process: %s\n", strerror(errnum));
    }

    exit(0);
}
