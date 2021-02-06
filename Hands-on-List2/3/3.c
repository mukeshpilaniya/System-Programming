#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#define ERROR_EXIT(msg) do{perror(msg); exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	struct rlimit rlim, rlim1;
	printf("Value of core file size before changing: ");
	if(getrlimit(RLIMIT_CORE, &rlim) == -1) ERROR_EXIT("getrlimit()");
	printf("%lu\n", rlim.rlim_cur);
	printf("Value of core file size after changing: ");
	rlim.rlim_cur = 1024;
	if(setrlimit(RLIMIT_CORE, &rlim) == -1) ERROR_EXIT("setrlimit()");
	if(getrlimit(RLIMIT_CORE, &rlim1) == -1) ERROR_EXIT("getrlimit()");
	printf("%lu\n", rlim1.rlim_cur);
	exit(EXIT_SUCCESS);
}