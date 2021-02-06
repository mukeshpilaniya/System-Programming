#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;

}arg;

int main(int argc, char const *argv[])
{
	int semid, semflag = 0644 | IPC_CREAT | IPC_EXCL;
	int nsems = 1;
	size_t nsops = 1;
	key_t key;
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	if((key = ftok(".", (int)'z')) == (key_t)-1)
		ERR_EXIT("ftok()");
	if((semid = semget(key, nsems, semflag)) == -1)
	{
		// if semaphore already exist the get the semid 
		if(errno == EEXIST)
		{
			// semaphore already exist opening it
			if((semid = semget(key, nsems, 0)) == -1)
				ERR_EXIT("semget()");
		}
		else ERR_EXIT("semget()");
	}
	else
	{
		// created semaphore setting value for binary or counting
		arg.val = 1;
		if(semctl(semid, buf.sem_num, SETVAL, arg) == -1)
			ERR_EXIT("semctl()");
	}
	printf("Before entering to critical section.\n");
	printf("Waiting for lock...\n");
	if(semop(semid, &buf, nsops) == -1)
		ERR_EXIT("semop()");
	printf("Inside critical section.\n");
	printf("Press return to exit critical section.\n");
	getchar();
	buf.sem_op = 1;
	if(semop(semid, &buf, nsops) == -1)
		ERR_EXIT("semop()");
	// if (semctl(semid, 0, IPC_RMID) == -1)
		// ERR_EXIT("semctl()");
	exit(EXIT_SUCCESS);
}