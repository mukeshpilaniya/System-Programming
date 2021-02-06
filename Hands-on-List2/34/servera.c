#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <port_number>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int socket_fd, conn_fd;
	struct sockaddr_in serv_addr;
	
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		ERR_EXIT("socket()");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		ERR_EXIT("bind()");
	
	if(listen(socket_fd, 10) == -1)
		ERR_EXIT("listen()");

	while(1)
	{
		if((conn_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1)
			ERR_EXIT("accept()");
		pid_t pid;
		if((pid = fork()) == -1) ERR_EXIT("fork()");
		else if(pid == (pid_t)0)
		{ //child process executes the task
			if(close(socket_fd) == -1) ERR_EXIT("close()");
			int size;
			if(read(conn_fd, &size, sizeof(size)) == -1) ERR_EXIT("read()");
			size = ntohl(size);
			if(size == -1) break;
			// int *arr = (int*)malloc(sizeof(int) * size);
			int sum = 0, var;
			for (int i = 0; i < size; ++i)
			{
				if(read(conn_fd, &var, sizeof(int)) == -1) ERR_EXIT("read()");
				sum += ntohl(var);
			}
			sum = htonl(sum);
			if(write(conn_fd, &sum, sizeof(sum)) == -1) ERR_EXIT("write()");
			if(close(conn_fd) == -1) ERR_EXIT("close()");
			exit(EXIT_SUCCESS);
		}
		else
		{ // parent close the connection
			if(close(conn_fd) == -1) ERR_EXIT("close()");
		}
	}
	close(socket_fd);
}