#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	long PIPE_BUF, OPEN_MAX;
	if((PIPE_BUF = pathconf(".", _PC_PIPE_BUF)) == -1)
		ERR_EXIT("pathconf()");
	if((OPEN_MAX = sysconf(_SC_OPEN_MAX)) == -1)
		ERR_EXIT("sysconf()");
	printf("Maximum number of bytes that can be written atomically to a pipe of FIFO: %ld bytes\n", PIPE_BUF);
	printf("Maximum number of files that can be opened by proces: %ld\n", OPEN_MAX);
	exit(EXIT_SUCCESS);
}