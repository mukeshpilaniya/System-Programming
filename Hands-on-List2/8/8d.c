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
		case SIGALRM: printf("Receieved SIGALRM.\n");
		break;
		default: printf("Invalid signal.\n");
	}
}

int main(int argc, char const *argv[])
{
	typedef void (* sighandler_t)(int);
	if(signal(SIGALRM, (sighandler_t)callback_fn) == SIG_ERR)
		ERR_EXIT("signal()");
	// raise the alarm after 2 seconds
	alarm(2);
	// wait for the alarm to be raised
	pause();	
	exit(EXIT_SUCCESS);
}