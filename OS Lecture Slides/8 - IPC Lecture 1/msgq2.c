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
        int msgid,retval,retval1;
        struct msgbuf buff;
        msgid=msgget((key_t)1231,IPC_CREAT|IPC_EXCL);
        if(msgid<0)
        {
                perror("error:");
                msgid=msgget(1231,0666);
                if(msgid<0)
                return 0;
        }
        printf("the msgid in process2 is %d\n",msgid);
        retval=msgrcv(msgid,&buff,12,1,0);
	if(retval<0)
        {
                perror("error sending");
        }

	printf("message from process2 is %s\n",buff.mtext);
	//retval1=msgctl(msgid,IPC_RMID,NULL);	
	//if(retval1<0)
	//{
	//	perror("unable to destuct memory");
	//}


return 0;
	
	
}
