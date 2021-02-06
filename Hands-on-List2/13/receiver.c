#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int sig)
{
	if(sig == SIGSTOP)
		printf("Caught SIGSTOP signal.\n");
}

int main(int argc, char const *argv[])
{
	printf("pid of the process: %d\n", getpid());
	typedef void (*handler_t)(int);
	// SIGSTOP can't be caught 
	if(signal(SIGSTOP, (handler_t)handler) == SIG_ERR)
	{
		perror("signal()");
		exit(EXIT_FAILURE);
	}
	// wait for signal
	sleep(100);
	exit(EXIT_SUCCESS);
}