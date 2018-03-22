#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

/*The following program counts the number of ascii characters and non-ascii characters, tallying them up and displaying the count as appropriate.*/

//Global variables declared

int aiicount = 0;
int naiicount = 0;
int asciinum;
char **fin;

//SIGUSR1 handler defined. 

void ascii_alert(int signum) {
	if (signum == SIGUSR1) {
		if (asciinum != 0)	
			aiicount++;
		else
			naiicount++;
	}
	
	else if (signum == SIGUSR2) {
		printf("Read file: %s", fin[1]);		
		printf("Number of ascii characters: %d\n\n", aiicount);
		printf("Number of non-ascii characters: %d\n\n", naiicount);	
	}	 			
}

int main(int argc, char **argv) {

	int l = 0;
	int z;
	char x;
	FILE *twitch;
	twitch = fopen(argv[1], "r");
	fin = argv;	

	if(!twitch) {
		fprintf(stderr, "Couldn't open file %s!\n\n", argv[1]);			
		perror("Error");
		exit(errno);	
		}
	else {
		printf("Opened file %s.\n\n", argv[1]);
		signal(SIGUSR1, ascii_alert);
		signal(SIGUSR2, ascii_alert);

		while (l != EOF) {
			l = fgetc (twitch);
			x = (char) l;
			asciinum = isascii(l);
			if (asciinum != 0) {			
				raise(SIGUSR1);
			}
			else {
				raise(SIGUSR1);
			}
		}
		z = fclose (twitch);
	
		if (z == 0)
			raise(SIGUSR2);
		else {
			perror("Close fail.");
			printf("%d\n\n", z);
			exit(errno);
		}
	
	}	
	
	return 0;
}
