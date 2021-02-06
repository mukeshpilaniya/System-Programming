#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	int msgid;
	key_t key;
	long msgtype = 0; // first message in the queue is read irrespective of type
	struct msg
	{
		long mtype;
		char message[80];
	}mq;
	
	if((key = ftok(".", (int)'a')) == (key_t)-1)
		ERR_EXIT("ftok()");
	if((msgid = msgget(key, 0644 | IPC_CREAT)) == -1)
		ERR_EXIT("msgget()");
	
	if(msgrcv(msgid, &mq, sizeof(mq), msgtype, IPC_NOWAIT) == -1)
		ERR_EXIT("msgrcv()");
	printf("Data recieved successfully from message queue.\n"); 
	printf("msgid: %d, message type: %ld and size: %lu.\nmessage: %s\n", msgid, mq.mtype, strlen(mq.message), mq.message);
	exit(EXIT_SUCCESS);
}