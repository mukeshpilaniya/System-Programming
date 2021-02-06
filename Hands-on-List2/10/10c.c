#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

void callback_fn(int sig, siginfo_t *info, void *ucontext)
{
	printf("Catched SIGFPE signal.\n");
}

int main(int argc, char const *argv[])
{
	struct sigaction sg;
	memset(&sg, 0, sizeof(sg));
	sg.sa_flags = SA_SIGINFO;
	sg.sa_sigaction = callback_fn;
	if(sigaction(SIGFPE, &sg, NULL) == -1) ERR_EXIT("sigaction()");
	if(kill(getpid(), SIGFPE) == -1) ERR_EXIT("kill()");
	exit(EXIT_SUCCESS);
}