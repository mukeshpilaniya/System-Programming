#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


unsigned long long rdtsc()
{
   unsigned long hi, lo;
   __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
   return ( (unsigned long long)lo ) | ( ( (unsigned long long)hi ) << 32 );
}

int main(int argc, char const *argv[])
{
	unsigned long long start, end; 
	int ppid;
	start = rdtsc();
	for (int i = 0; i < 100; ++i) ppid = getppid();
	end = rdtsc();
	unsigned long long number_of_ticks = end - start;
	unsigned long long freq_ghz = 2.993246;
	unsigned long long ns = number_of_ticks / freq_ghz;
    printf("CPU time used to execute 100 getpid(): %llu nsec\n", ns); 
    double usec = (double) ns / (double)1000;
    printf("CPU time used to execute 100 getpid(): %lf usec or %e usec\n", usec, usec);
    double sec = (double)ns / (double)1000000000;
	printf("CPU time used to execute 100 getpid(): %lf sec or %e sec.\n", sec, sec);
	exit(EXIT_SUCCESS);
}