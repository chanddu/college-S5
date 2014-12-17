#include <sys/ipc.h>
#include <sys/shm.h>
#include<stdio.h>
#include <sys/types.h>
#include<string.h>

int main()
{
        int shmid,retval;
        void *memory;
        shmid=shmget(1234,12,IPC_CREAT|IPC_EXCL);
        if(shmid<0)
        {
                perror("shmget error:");
                shmid=shmget(1234,12,0666);
                if(shmid<0)
                {
                        perror("shmget");
                        return 0;
                }
        }
        printf("shmid for process1 is %d\n",shmid);

        memory=shmat(shmid,NULL,0);
        if(memory==NULL)
        {
                perror("shmat:");
                return 0;
        }
	
	printf("the msg from process1 is %s\n",memory);
	retval=shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
	

