#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<string.h>

union semun 
{
	int val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                         (Linux-specific) */
};


int main()
{
	
	union semun un;
	struct sembuf buf;
	int semid,retval;
	semid=semget(1209,1,IPC_CREAT|IPC_EXCL);
	if(semid>=0)
	{
		un.val=1;
		retval=semctl(semid,0,SETVAL,un);
	}
	else
	{
		semid=semget(1209,1,0666);
		if(semid<0)
		{
			perror("semget:");
			return 0;
		}
	}
	buf.sem_num=0;
	buf.sem_op=-1;
	buf.sem_flg=SEM_UNDO;
	retval=semop(semid,&buf,1);
	if(retval<0)
	{
		perror("semop");
		return 0;
	}
	//critical se ction
	printf("in criticaL SECTION\n");
	sleep(10);
	buf.sem_num=0;
        buf.sem_op=1;
        buf.sem_flg=SEM_UNDO;
        retval=semop(semid,&buf,1);
        if(retval<0)
        {
                perror("semop");
                return 0;
        }

}

