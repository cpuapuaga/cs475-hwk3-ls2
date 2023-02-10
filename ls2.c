#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"


// TODO: function definitions here for ls2
int offset = 0;

/**
 * Checks whether or not the directory is readable. If so, passes it on to travDir.
 * Otherwise, prints an error message
*/
void validDir(char *path){
    if(opendir(path) == NULL){
        printf("Couldn't find directory: %s\n", path);
    }
    travDir(path);
    
}

/**
 * Function that recursively traverses a given directory
*/
void travDir(char *path){
    static int visited_dirs[1024] = {1};
    static int count = 0;

    DIR *d = opendir("./");
    struct dirent *dir;
    struct stat stats; 
    char *next;


    while((dir = readdir(d)) != NULL){
        next = malloc(strlen(path) + strlen(dir->d_name)+2);
        strcpy(next, path);
        strcat(next, "/");
        strcat(next,dir->d_name);
        lstat(next, &stats);
        
        if(S_ISDIR(stats.st_mode)){
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                for(int i=0; i<offset; i++){
                    printf(INDENT);
                }
                offset++;
                printf("%s/ (Directory)\n", dir->d_name);
                if (visited_dirs[count] == 1) {
                    visited_dirs[count] = 0;
                    count++;
                    travDir(next);
                }
                offset--;
            }
        } else if (S_ISREG(stats.st_mode)){
            for (int i=0; i<offset; i++) {
                printf(INDENT);
            }
            printf("%s (%ld bytes)\n", dir->d_name, stats.st_size);
        }
        free(next);
    }
    closedir(d);
}
