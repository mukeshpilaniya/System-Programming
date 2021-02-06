#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	kill(atoi(argv[1]), SIGSTOP);
	printf("does this?\n");
	exit(EXIT_SUCCESS);
}