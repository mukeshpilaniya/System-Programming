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
		// closing read end of the pipe
		if(close(fd[0]) == -1) ERR_EXIT("close()");
		// closing STDOUT and assingning it to the fd[1]
		if(dup2(fd[1], STDOUT_FILENO) == -1) ERR_EXIT("dup2()");
		// executing `ls -lh` and the output goes to the pipe
		// since it is performing as stdout
		if(execlp("ls", "ls", "-lh", (char *) NULL) == -1)
			ERR_EXIT("execlp()");
	}
	else
	{
		// closing write end of the pipe
		if(close(fd[1]) == -1) ERR_EXIT("close()");
		// fd[0] will now work as STDIN
		if(dup2(fd[0], STDIN_FILENO) == -1) ERR_EXIT("dup2()");
		if(execlp("wc", "wc", (char *) NULL) == -1)
			ERR_EXIT("execlp()");
	}
}