#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h> 

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char *argv[])
{
    int socket_fd;
    ssize_t n;
    char recvBuff[1024];
    struct sockaddr_in server_addr; 

    if(argc != 3)
    {
        fprintf(stderr ,"Usage: %s <ip_addr_of_server> <port_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    
    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        ERR_EXIT("socket()");

    memset(&server_addr, '0', sizeof(server_addr)); 

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2])); 

    if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
        ERR_EXIT("inet_pton()"); 

    if(connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        ERR_EXIT("connect()");
    printf("Sum numbers.\n");
    printf("How many numbers you want to sum: ");
    int size;
    scanf("%d", &size);
    size = htonl(size);
    if(write(socket_fd, &size, sizeof(size)) == -1) ERR_EXIT("write()");
    size = ntohl(size);
    int val;
    printf("Enter %d numbers: ", size);
    for (int i = 0; i < size; ++i) 
    {
        scanf("%d", &val);
        val = htonl(val);
        if(write(socket_fd, &val, sizeof(val)) == -1) ERR_EXIT("write()");
    }
    read(socket_fd, &val, sizeof(val));
    val = ntohl(val);
    printf("Sum of numbers: %d\n", val);
    close(socket_fd);
    exit(EXIT_SUCCESS);
}