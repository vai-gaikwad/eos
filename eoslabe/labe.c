#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include<pthread.h>
#include<math.h>

#define MQ_KEY		0x1234

typedef struct msg {
	long type;
	int x;
} msg_t;

typedef struct mseg {
	long type;
	int z;
} msg_t2;

int mqid;

void* thread1(void * param)
{		
		int ret;
        msg_t m1;
		m1.type = 1;
		printf("thread1 : enter a number to get its square root: \n");
		scanf("%d", &m1.x);
		ret = msgsnd(mqid, &m1,(sizeof(int)), 0);
		printf("thread1 :sent\n");
		
		msg_t2 m3;
		printf("thread1: waiting for the answer...\n");
		ret = msgrcv(mqid, &m3, sizeof(int), 2, 0);
		printf("thread1 received: answer  -- %d\n", m3.z);
		return 0;

}


void * thread2(void* param)
{

		int ret;
		msg_t m2;
		printf("thread 2 : waiting  for num \n");
		ret = msgrcv(mqid, &m2, (sizeof(int)), 1, 0);
		printf("thread 2:: numbers recieved: %d\n",m2.x);
		int x=m2.x;

		int z=sqrt(x);
		
		msg_t2 m4;
		m4.type = 2;
		printf("thread 2 sender:\n");
		m4.z=z;
		ret = msgsnd(mqid, &m4,sizeof(int), 0);
		printf("thread 2: answer sent\n");
		return 0;
}


int main() {
	int ret, s;
	pthread_t t1,t2;
	printf("hello\n");
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid < 0) {
		perror("msgget() failed");
		_exit(1);
	}

ret = pthread_create(&t1, NULL,thread1,NULL);
if (ret<0)
{
perror("pthread_create failed");
}
ret = pthread_create(&t2, NULL,thread2,NULL);
       
if (ret<0)
{
perror("pthread_create failed");
}

 printf("wait");
 scanf("%d",&s);
	   msgctl(mqid, IPC_RMID, NULL);
	
	return 0;
}


