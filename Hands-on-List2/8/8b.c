#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

void callback_fn(int signal_number)
{
	switch(signal_number)
	{
		case SIGINT: printf("Receieved SIGINT.\n");
		break;
		default: printf("Invalid signal.\n");
	}
}

int main(int argc, char const *argv[])
{
	typedef void (* sighandler_t)(int);
	if(signal(SIGINT, (sighandler_t)callback_fn) == SIG_ERR)
		ERR_EXIT("signal()");
	
	if(kill(getpid(), SIGINT) == -1) ERR_EXIT("kill()");
	
	exit(EXIT_SUCCESS);
}