#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

void sum_numbers(int *conn_fd)
{
	int size;
	if(read(*conn_fd, &size, sizeof(size)) == -1) ERR_EXIT("read()");
	size = ntohl(size);
	int sum = 0, var;
	for (int i = 0; i < size; ++i)
	{
		if(read(*conn_fd, &var, sizeof(int)) == -1) ERR_EXIT("read()");
		sum += ntohl(var);
	}
	sum = htonl(sum);
	if(write(*conn_fd, &sum, sizeof(sum)) == -1) ERR_EXIT("write()");
	if(close(*conn_fd) == -1) ERR_EXIT("close()");
}

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
		pthread_t th;
		if(pthread_create(&th, NULL, (void*)sum_numbers, (void*)&conn_fd) != 0)
			ERR_EXIT("pthread_create()");
	}
	close(socket_fd);
}