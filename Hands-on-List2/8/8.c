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
		case SIGSEGV: printf("Receieved SIGSEGV.\n");
		break;
		case SIGINT: printf("Receieved SIGINT.\n");
		break;
		case SIGFPE: printf("Receieved SIGFPE.\n");
		break;
		case SIGALRM: printf("Receieved SIGALRM.\n");
		break;
		case SIGVTALRM: printf("Receieved SIGVTALRM.\n");
		break;
		case SIGPROF: printf("Receieved SIGPROF.\n");
		break;
		default: printf("Invalid signal.\n");
	}
}

int main(int argc, char const *argv[])
{
	typedef void (* sighandler_t)(int);
	if(signal(SIGSEGV, (sighandler_t)callback_fn) == SIG_ERR)
		ERR_EXIT("signal()");
	if(signal(SIGINT, (sighandler_t)callback_fn) == SIG_ERR)
		ERR_EXIT("signal()");
	if(signal(SIGFPE, (sighandler_t)callback_fn) == SIG_ERR)
		ERR_EXIT("signal()");
	if(signal(SIGALRM, (sighandler_t)callback_fn) == SIG_ERR)
		ERR_EXIT("signal()");
	if(signal(SIGVTALRM, (sighandler_t)callback_fn) == SIG_ERR)
		ERR_EXIT("signal()");
	if(signal(SIGPROF, (sighandler_t)callback_fn) == SIG_ERR)
		ERR_EXIT("signal()");
	
	if(kill(getpid(), SIGSEGV) == -1) ERR_EXIT("kill()");
	if(kill(getpid(), SIGINT) == -1) ERR_EXIT("kill()");
	if(kill(getpid(), SIGFPE) == -1) ERR_EXIT("kill()");
	if(kill(getpid(), SIGALRM) == -1) ERR_EXIT("kill()");
	if(kill(getpid(), SIGVTALRM) == -1) ERR_EXIT("kill()");
	if(kill(getpid(), SIGPROF) == -1) ERR_EXIT("kill()");
	
	exit(EXIT_SUCCESS);
}