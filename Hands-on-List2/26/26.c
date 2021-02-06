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
	size_t size;
	key_t key;
	struct msg
	{
		long mtype;
		char message[80];
	}mq;
	if((key = ftok(".", (int)'a')) == (key_t)-1)
		ERR_EXIT("ftok()");
	if((msgid = msgget(key, 0644 | IPC_CREAT)) == -1)
		ERR_EXIT("msgget()");
	printf("Enter the message type: ");
	scanf("%ld", &(mq.mtype));
	printf("Enter the message: ");
	scanf(" %[^\n]", mq.message);
	size = strlen(mq.message);

	if(msgsnd(msgid, &mq, size + 1, 0) == -1)
		ERR_EXIT("msgsnd()");
	printf("Data sent successfully to message queue.\n"); 
	printf("msgid: %d, message type: %ld and size: %lu.\nmessage: %s\n", msgid, mq.mtype, size, mq.message);
	exit(EXIT_SUCCESS);
}