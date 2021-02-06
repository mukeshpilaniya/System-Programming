#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void callback_fn(int signal_number)
{
	switch(signal_number)
	{
		case SIGPROF: printf("Receieved SIGPROF.\n");
		break;
		default: printf("Invalid signal.\n");
	}
}


int main(int argc, char const *argv[])
{
	struct itimerval it_val;
	typedef void (* sighandler_t)(int);
	if(signal(SIGPROF, (sighandler_t)callback_fn) == SIG_ERR)
	{
		perror("signal()");
		exit(EXIT_FAILURE);
	}
	// timer will expire intially after 1 second and 250 micro seconds
	it_val.it_value.tv_sec = 1;
	it_val.it_value.tv_usec = 250;
	// and then at interval of 1 second and 10 microsecond
	it_val.it_interval.tv_sec = 1;
	it_val.it_interval.tv_usec = 10;

	if(setitimer(ITIMER_PROF, &it_val, NULL) == -1)
	{
		perror("setitimer()");
		exit(EXIT_FAILURE);
	}
	while(1);
	exit(EXIT_SUCCESS);
}