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
	char buf1[512], buf2[512];
	ssize_t count; 
	while(1)
	{
		// take input from stdin in buf1 and write it to fifo 
		if((fd = open(argv[1], O_WRONLY)) == -1) ERR_EXIT("open()");
		if((count = read(STDIN_FILENO, buf1, sizeof(buf1))) == -1) ERR_EXIT("read()");
		buf1[count] = '\0';
		if(write(fd, buf1, strlen(buf1) + 1) == -1) ERR_EXIT("write()");
		if(close(fd) == -1) ERR_EXIT("close()");

		// read from fifo and write to stdout
		if((fd = open(argv[1], O_RDONLY)) == -1) ERR_EXIT("open()");
		if(read(fd, buf2, sizeof(buf2)) == -1) ERR_EXIT("read()");
		if(write(STDOUT_FILENO, buf2, strlen(buf2)) == -1) ERR_EXIT("write()");
		if(close(fd) == -1) ERR_EXIT("close()");
	}
}