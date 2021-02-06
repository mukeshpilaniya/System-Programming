#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>

void show_error(const char *fn_name)
{
	perror(fn_name);
	exit(EXIT_FAILURE);
}

void print_rlimit(struct rlimit *rlim, const char *name, const char *unit)
{
	rlim_t rlim_cur, rlim_max; //soft limit and hard limit
	rlim_cur = rlim->rlim_cur;
	rlim_max = rlim->rlim_max;
	printf("%3s %-18s ", "Max", name);
	if(rlim_cur == ULONG_MAX) printf("%-18s", "unlimited");
	else printf("%-18lu", rlim_cur);
	if(rlim_max == ULONG_MAX) printf("%-18s", "unlimited");
	else printf("%-18lu", rlim_max);
	printf("%-18s", unit);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	struct rlimit rlim;
	int limits[16] = {RLIMIT_AS, RLIMIT_CORE, RLIMIT_CPU, RLIMIT_DATA,
					RLIMIT_FSIZE, RLIMIT_LOCKS, RLIMIT_MEMLOCK,
					RLIMIT_MSGQUEUE, RLIMIT_NICE, RLIMIT_NOFILE, RLIMIT_NPROC,
					RLIMIT_RSS, RLIMIT_RTPRIO, RLIMIT_RTTIME, RLIMIT_SIGPENDING,
					RLIMIT_STACK};
	const char *names[16] = {"address space", "core file size", "cpu time",
						"data size", "file size", "file locks", "locked memory",
						"msgqueue size", "nice priority", "open files",
						"processes", "resident set", "realtime priority",
						"realtime timeout", "pending signals", "stack size"};
	const char *units[16] = {"bytes", "bytes", "seconds", "bytes", "bytes", "locks",
							"bytes", "bytes", "", "files", "processes", "bytes", "",
							"us", "signals", "bytes"};
	printf("%-22s %-18s%-18s%-18s", "Limit", "Soft Limit", "Hard Limit", "Units");
	printf("\n=================================================================\n");
	for (int i = 0; i < 16; ++i)
	{
		if(getrlimit(limits[i], &rlim) == -1) show_error("getrlimit()");
		print_rlimit(&rlim, names[i], units[i]);
	}
	exit(EXIT_SUCCESS);
}