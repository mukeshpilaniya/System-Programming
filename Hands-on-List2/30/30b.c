#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main(int argc, char const *argv[])
{
	int shmid, shmflag = 0644 | IPC_CREAT | SHM_RDONLY;
	size_t size = 1024;
	key_t key;
	char *data;
	if((key = ftok(".", (int)'a')) == (key_t)-1)
		ERR_EXIT("ftok()");
	
	if((shmid = shmget(key, size, shmflag)) == -1)
		ERR_EXIT("shmget()");
	if((data = (char*)shmat(shmid, NULL, shmflag)) == (void*)-1)
		ERR_EXIT("shmat()");
	printf("Enter the data you want to write to shared memomry: ");
	scanf(" %[^\n]", data);
	printf("Data: %s\n", data);
	if(shmdt(data) == -1) ERR_EXIT("shmdt()");
	exit(EXIT_SUCCESS);
}