#include <stdio.h> 
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{ 
	key_t key;
	if((key = ftok(".", (int)'a')) == -1) ERR_EXIT("ftok()");
	int msgid;
	if((msgid = msgget(key, 0644 | IPC_CREAT)) == -1) ERR_EXIT("msgget()");
	printf("Key = %d\n", key);
	printf("Msgid = %d\n", msgid);
	exit(EXIT_SUCCESS); 
} 