#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

struct dirent *dirEnt;

//  If no directory is passed as an argument, we ust want to print the files in the directory. We also don't want to print `.` or `..` since those aren't exactly the most helpful if we are looking for a file.
  if (argv[1] == NULL) {
  DIR *dr = opendir(".");
  if (dr == NULL) {
    fprintf(stderr, "directory not available\n");
  } else {
     while ((dirEnt = readdir(dr)) != NULL) {
       
        if ( (strcmp(dirEnt->d_name, ".") != 0) && (strcmp(dirEnt->d_name, "..") != 0)) {

       printf("%s\n", dirEnt->d_name);
     }
  }
  }
  closedir(dirEnt);
  } else {
    DIR *dr = opendir(argv[1]);
    if (dr == NULL) {   
    fprintf(stderr, "directory not available\n");
    } else {
      while ((dirEnt = readdir(dr)) != NULL) {
        if ( (strcmp(dirEnt->d_name, ".") != 0) && (strcmp(dirEnt->d_name, "..") != 0)) { 
          printf("%s\n", dirEnt->d_name);

        }
      }

    }
    closedir(dirEnt);
  }
  return 0;
}
