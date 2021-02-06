#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	int fd[2];
	pid_t pid;

	if(pipe(fd) == -1) ERR_EXIT("pipe()");

	if((pid = fork()) == -1) ERR_EXIT("fork()");
	else if(pid == 0)
	{
		//closing stdout fd
		if(close(STDOUT_FILENO) == -1) ERR_EXIT("close()");
		// closing read end of the pipe
		if(close(fd[0]) == -1) ERR_EXIT("close()");
		// duplicating fd[1] with least number available
		// that is of STDOUT
		if(dup(fd[1]) == -1) ERR_EXIT("dup()");
		// executing `ls -lh` and the output goes to the pipe
		// since it is performing as stdout
		if(execlp("ls", "ls", "-lh", (char *) NULL) == -1)
			ERR_EXIT("execlp()");
		// close(fd[1]);
	}
	else
	{
		//closing stdin
		if(close(STDIN_FILENO) == -1) ERR_EXIT("close()");
		// closing write end of the pipe
		if(close(fd[1]) == -1) ERR_EXIT("close()");
		// fd[0] will now work as STDIN
		if(dup(fd[0]) == -1) ERR_EXIT("dup()");
		if(execlp("wc", "wc", (char *) NULL) == -1)
			ERR_EXIT("execlp()");
	}
}