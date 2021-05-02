#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


void sigintHandler(int sig){
  signal(SIGINT, sigintHandler);
  printf("\nGrab Ctrl+C blocked.\n");
  //    exit(0);
}

int main(int argc, char *argv[]) {
  signal(SIGINT, sigintHandler);
  char cwd[500];
  char mylsdir[100];
  getcwd(mylsdir, sizeof(mylsdir));
  strcat(mylsdir, "/ls");
  int rc;
  char *home = getenv("HOME");
  char *user = getenv("USER");
  while (1){

    printf("%s %s ", user, "$");
    char *args1[20];
    char cmd[50];
    if(fgets(cmd, 50, stdin) == NULL){
      exit(0);
    }
    char *token = strtok(cmd, "\n");
    token = strtok(token, "\v");
    token = strtok(token, "\t");
    token = strtok(token, " ");
    int i = 0;
    while(token != NULL){
      args1[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    int cmdNum = -1;
    //Commands = cd, ls, myls, redir, help, ...
    //cd = 0, myls = 1, ls = 2, redir = 3, help = 4, ...
    if (strcmp(args1[0], "cd") == 0){
      cmdNum = 0;
    } else if (strcmp(args1[0], "myls") == 0){
      cmdNum = 1;
    } else if (strcmp(args1[0], "ls") == 0){
      cmdNum = 2;
    } else if (strcmp(args1[0], "mkdir") == 0){
      cmdNum = 3;
    } else if (strcmp(args1[0], "help") == 0){
      cmdNum = 4;
    } else if (strcmp(args1[0], "pwd") == 0){
      cmdNum = 5;
    } else if (strcmp(args1[0], "clear") == 0) {
      cmdNum = 6;
    }

    switch(cmdNum){
    case 0:
      //      printf("Run cd option\n");
      if ((strcmp(args1[1], "~") == 0) || (args1[1] == NULL)) {
        chdir(home);
        getcwd(cwd, sizeof(cwd));
        printf("New current working directory is: %s\n", cwd);
      } else {
                  
        chdir(args1[1]);
        getcwd(cwd, sizeof(cwd));
        printf("New current working directory is: %s\n", cwd);
      }
      break;

    case 1:
      printf("\n");
      rc = fork();
      if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
      } else if (rc == 0) {
        char *args[] = {mylsdir, ".", NULL};
          execvp(args[0],args);
          exit(0);
      } else {
        wait(NULL);
      }

      printf("\n");
      break;
    case 2:
      //printf("run native ls\n");
      printf("\n");
      rc = fork();
      if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
      } else if (rc == 0) {
        char *args[] = {"/bin/ls", "-1AU", "--color=always", ".", NULL};
          execvp(args[0],args);
          exit(0);
      } else {
        wait(NULL);
      }

      printf("\n");


      break;
    case 3:
      //printf("Run mkdir\n");
      if (mkdir(args1[1], 0777) != 0){
          fprintf(stderr, "mkdir failed\n");
      }
      break;
    case 4:
      printf("Commands are:\ncd\nmyls\nls\nmkdir\nhelp\npwd\nclear\n");
      break;
    case 5:
      getcwd(cwd, sizeof(cwd));
      printf("cwd is: %s\n", cwd);
      break;
    case 6:
      system("/usr/bin/clear");
      break;
    default:
      //  printf("Use command 'help' to see commands.\n");
      break;
    }
  }
}
