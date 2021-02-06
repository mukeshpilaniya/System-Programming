#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <message_queue_id> <permissions_in_octal>\n", argv[0]);
		fprintf(stderr, "example: %s 65538 666\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	struct msqid_ds msq;

	if(msgctl(atoi(argv[1]), IPC_STAT, &msq) == -1)
		ERR_EXIT("msgctl()");

	printf ("The access permissions before modification = 0%o\n",msq.msg_perm.mode);
	
	msq.msg_perm.mode = (unsigned short)strtol(argv[2], NULL, 8);
	if(msgctl(atoi(argv[1]), IPC_SET, &msq) == -1)
		ERR_EXIT("msgctl()");

	if(msgctl(atoi(argv[1]), IPC_STAT, &msq) == -1)
		ERR_EXIT("msgctl()");

	printf ("The access permissions after modification = 0%o\n",msq.msg_perm.mode);
	
	exit(EXIT_SUCCESS); 
} 