#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 * 
 * Unfinished code. Does not include mode 2
 */
int main(int argc, char* argv[]) {
	char path[strlen(argv[1])];
	//mode 1
	if(argc == 2){
		strcpy(path, argv[1]);
		validDir(path);
	}
	return 0;
}
