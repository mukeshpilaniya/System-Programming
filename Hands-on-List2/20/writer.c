#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <fifo_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd;
	char buf[512];
	ssize_t count; 
	while(1)
	{
		if((fd = open(argv[1], O_WRONLY)) == -1) ERR_EXIT("open()");
		if((count = read(STDIN_FILENO, buf, sizeof(buf))) == -1) ERR_EXIT("read()");
		buf[count] = '\0';
		if(write(fd, buf, strlen(buf) + 1) == -1) ERR_EXIT("write()");
		if(close(fd) == -1) ERR_EXIT("close()");
		if(strcmp(buf, "exit\n") == 0) exit(EXIT_SUCCESS);
	}
}