#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define PIPE_NAME "/tmp/pipe"
#define BUF_SIZE 100


int mkfifo(const char *path_name, mode_t mode);

int main(int argc, char ** argv){
	int fd, read_bytes;
	char k;
	char buf[BUF_SIZE];
	
	// Create named pipe
	if (mkfifo(PIPE_NAME, 0666)){
		perror("mkfifo");
		printf("Wanna create new named pipe? 'Y/n':\n");
		scanf("%s", &k);
		if (k == 'y' || k == 'Y')
			mkfifo(PIPE_NAME, 0666);
		else
			exit(1);
	}
	printf("%s is created\n", PIPE_NAME);
	
	
	while (1) {
	
		// Opening named pipe for reading
		if ( (fd = open(PIPE_NAME, O_RDONLY)) == -1 ){	
			perror("open");
			exit(2);
		}	
		
		// Getting data from pipe
		read_bytes = read(fd, buf, sizeof(buf));
		buf[read_bytes] = '\0';

		close(fd);

		// Check for exit condition
		if(strcmp(buf, "exit\n") == 0)
			break; // Exit the loop			
		
		printf("Incomming message: %s", buf);
	}
	
	remove(PIPE_NAME);
	return 0;
}
