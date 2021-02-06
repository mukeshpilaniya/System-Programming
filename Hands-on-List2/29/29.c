#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <message_queue_id>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("Removing msgq with msgid: %s\n", argv[1]);
	if(msgctl(atoi(argv[1]), IPC_RMID, NULL) == -1)
		ERR_EXIT("msgctl()");
	printf ("msgq removed successfully.\n");
	exit(EXIT_SUCCESS); 
} 