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
		fprintf(stderr, "Usage: %s <message queue id>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	struct msqid_ds msq;
	
	if(msgctl(atoi(argv[1]), IPC_STAT, &msq) == -1)
		ERR_EXIT("msgctl()");

	printf ("The access permissions = 0%o\n",msq.msg_perm.mode);
	printf ("The USER ID = %d\n",msq.msg_perm.uid);
	printf ("The GROUP ID = %d\n",msq.msg_perm.gid);
	printf ("The msg_qbytes = %lu\n",msq.msg_qbytes);
	printf ("Time of last msg sent = %lu\n",msq.msg_stime);
	printf ("Time of last msg receive = %lu\n",msq.msg_rtime);
	printf ("Time of last msg change = %lu\n",msq.msg_ctime);
	printf ("Current number of bytes in queue = %lu\n",msq.__msg_cbytes);
	printf ("Current number of messages in queue = %lu\n",msq.msg_qnum);
	printf ("Maximum number of bytes allowed  = %lu\n",msq.msg_qbytes);
	printf ("Pid of last message sent = %d\n",msq.msg_lspid);
	printf ("Pid of last message received = %d\n",msq.msg_lrpid);

	exit(EXIT_SUCCESS); 
} 