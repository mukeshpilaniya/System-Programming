#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	struct sigaction sg;
	memset(&sg, 0, sizeof(sg));
	
	sg.sa_flags = 0;
	sg.sa_handler = SIG_IGN;
	if(sigaction(SIGINT, &sg, NULL) == -1) ERR_EXIT("sigaction()");
	printf("Ignoring signal SIGINT.\n");
	sleep(5);

	printf("\nResetting to default.\n");
	sg.sa_handler = SIG_DFL;
	if(sigaction(SIGINT, &sg, NULL) == -1) ERR_EXIT("sigaction()");
	sleep(5);

	exit(EXIT_SUCCESS);
}