#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	long val;
	if((val = sysconf(_SC_ARG_MAX)) == -1) ERR_EXIT("sysconf");
    else printf("Maximum length of the arguments to the exec family of functions: %ld\n", val);
    
    if((val = sysconf(_SC_CHILD_MAX)) == -1) ERR_EXIT("sysconf");
    else printf("Maximum number of simultaneous process per user id: %ld\n", val);
    
    if((val = sysconf(_SC_CLK_TCK)) == -1) ERR_EXIT("sysconf");
    else printf("Number of clock ticks (jiffy) per second.: %ld\n", val);
    
    if((val = sysconf(_SC_OPEN_MAX)) == -1) ERR_EXIT("sysconf");
    else printf("Maximum number of open files: %ld\n", val);
    
    if((val = sysconf(_SC_PAGESIZE)) == -1) ERR_EXIT("sysconf");
    else printf("Size of a page: %ld\n", val);
    
    if((val = sysconf(_SC_PHYS_PAGES)) == -1) ERR_EXIT("sysconf");
    else printf("Total number of pages in the physical memory: %ld\n", val);
    
    if((val = sysconf(_SC_AVPHYS_PAGES)) == -1) ERR_EXIT("sysconf");
    else printf("Number of currently available pages in the physical memory: %ld\n", val);
    
    exit(EXIT_SUCCESS);
}