#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
		// duplicating fd[1] with STDOUT now 1 will have the same
		// pipe file opened as fd[1]
		int tfd;
		if((tfd = fcntl(fd[1], F_DUPFD, STDOUT_FILENO)) == -1) ERR_EXIT("fcntl()");
		if(tfd != STDOUT_FILENO)
		{
			fprintf(stderr, "Unable to clone pipe's write end to the STDOUT file descriptor.\n");
			exit(EXIT_FAILURE);
		}
		// fd[1] can be closed as file descriptor 1 has this value
		if(close(fd[1]) == -1) ERR_EXIT("close()");
		// executing `ls -lh` and the output goes to the pipe
		// since it is performing as stdout
		if(execlp("ls", "ls", "-lh", (char *) NULL) == -1)
			ERR_EXIT("execlp()");
	}
	else
	{
		//closing stdin
		if(close(STDIN_FILENO) == -1) ERR_EXIT("close()");
		// closing write end of the pipe
		if(close(fd[1]) == -1) ERR_EXIT("close()");
		// fd[0] will now work as STDIN
		int tfd;
		if((tfd = fcntl(fd[0], F_DUPFD, STDIN_FILENO)) == -1) ERR_EXIT("fcntl()");
		if(tfd != STDIN_FILENO)
		{
			fprintf(stderr, "Unable to clone pipe's read end to the STDIN file descriptor.\n");
			exit(EXIT_FAILURE);
		}
		if(execlp("wc", "wc", (char *) NULL) == -1)
			ERR_EXIT("execlp()");
	}
}