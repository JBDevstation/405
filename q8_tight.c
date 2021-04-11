#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
 * Macros from stdlib.h
 *  EXIT_SUCCESS is 0 in Posix, EXIT_FAILURE is 1 in Posix
 * Macros from unistd.h
 *  STDIN_FILENO is 1, STDOUT_FILENO is 1, STDERR_FILENO is 2
 *  NOTE: stdin is a FILE*, STDIN_FILENO is a number
 *   fprintf works with FILE*, write works with integers
 * pipe[0] is the input end, and FD 0 is STDIN_FILENO
 * pipe[1] is the output end, and FD 1 is STDOUT_FILENO
 *
 */

int main(int argc, char *argv[]) {
    if (argc == 1) {
	fprintf(stderr, "usage: q8 <string>\n");
	exit(EXIT_FAILURE);
    }
    printf("Program has parent and two children connected via a pipe.\n");
    printf("EXIT_SUCCESS: %d, EXIT_FAILIRE: %d\n", EXIT_SUCCESS, EXIT_FAILURE);
    int pipefd[2];
    pipe(pipefd);
    char buf = 'x';
    int child1 = fork();
    if (child1 == 0) { // child number 1 - reads from pipe
        printf("child 1: pipe reader: (pid:%d)\n", (int) getpid());
        close(pipefd[1]);
        while (read(pipefd[0], &buf, 1) > 0) // read one byte at a time
            write(1, &buf, 1);
        close(pipefd[0]);
        char argv1_rev[100];
        int i, j;
        for (i = strlen(argv[1])-1, j = 0; i >= 0; i--, j++)
            argv1_rev[j] = argv[1][i];
        write(1, argv1_rev, strlen(argv[1]));
        write(1, "\n", 1);
        exit(EXIT_SUCCESS);
    }
    int child2 = fork();
    if (child2 == 0) { // child number 2 - writes to pipe
        printf("child 2: pipe writer: (pid:%d)\n", (int) getpid());
        close(pipefd[0]); 
        write(pipefd[1], argv[1], strlen(argv[1]));
        write(pipefd[1], "Cooper", 6);
        close(pipefd[1]);          /* Reader will see EOF */
        exit(EXIT_SUCCESS);
    }
    // Parent
    close(pipefd[0]);
    close(pipefd[1]);
    printf("parentpid:%d of child1pid:%d and child2pid:%d \n", (int) getpid(), child1, child2);
    printf("childpid: %d finished\n", wait(NULL));
    printf("childpid: %d finished\n", wait(NULL));
    exit(EXIT_SUCCESS);
    return 0;
}
