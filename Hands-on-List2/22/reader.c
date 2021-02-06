#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
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
	fd_set rfds;//, wfds;
	struct timeval tv;
	int retval;
	while(1)
	{
		if((fd = open(argv[1], O_RDONLY)) == -1) ERR_EXIT("open()");
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		tv.tv_sec = 2;tv.tv_usec = 0;
		if((retval = select(fd + 1, &rfds, NULL, NULL, &tv)) == -1)
			ERR_EXIT("select()");
		else if(retval)
		{
			if(read(fd, buf, sizeof(buf)) == -1)
				ERR_EXIT("read()");
			if(write(STDOUT_FILENO, buf, strlen(buf)) == -1)
				ERR_EXIT("write()");
		}
		else
		{
			if(write(STDOUT_FILENO, "Failed to get data.\n", 20) == -1)
				ERR_EXIT("write()");
		}
		if(close(fd) == -1) ERR_EXIT("close()");
		if(strcmp(buf, "exit\n") == 0) exit(EXIT_SUCCESS);
	}
}