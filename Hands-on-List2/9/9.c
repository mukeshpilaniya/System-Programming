#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	printf("Ignoring the SIGINT signal.\n");
	if(signal(SIGINT, SIG_IGN) == SIG_ERR) ERR_EXIT("signal()");
	sleep(5);
	printf("\nResetting to default.\n");
	if(signal(SIGINT, SIG_DFL) == SIG_ERR) ERR_EXIT("signal()");
	sleep(5);
	exit(EXIT_SUCCESS);
}