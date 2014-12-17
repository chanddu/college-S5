#include<stdio.h>
#include<sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include<string.h>
struct msgbuf 
{
         long mtype;       /* message type, must be > 0 */
         char mtext[12];    /* message data */
};

int main()
{
	int msgid,retval;
	struct msgbuf buf;
	msgid=msgget((key_t)1231,IPC_CREAT|IPC_EXCL);
	if(msgid<0)
	{
		perror("error:");
		msgid=msgget(1231,0666);
		if(msgid<0)
		return 0;
	}
	printf("the msgid in process1 is %d",msgid);
	//ppacking the pKt
	buf.mtype=1;
	memcpy(buf.mtext,"HELLO WORLD",12);
	retval=msgsnd(msgid,&buf,12,0);
	if(retval<0)
	{
		perror("error sending");
	}
	return 0;
}
		
	
