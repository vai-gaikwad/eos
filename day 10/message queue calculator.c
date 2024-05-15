#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MQ_KEY		0x1234

typedef struct msg {
	long type;
	int x;
	int y;
} msg_t;

typedef struct mseg {
	long type;
	int z;
} msg_t2;

int main() {
	int mqid, ret, s;
	// create message queue
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid < 0) {
		perror("msgget() failed");
		_exit(1);
	}

	ret = fork();
	if(ret == 0) {
		// child: initialize and send the message
		msg_t m1;
		m1.type = 1;
		printf("child sender: enter two numbers: \n");
		scanf("%d%d", &m1.x,&m1.y);
		ret = msgsnd(mqid, &m1,(sizeof(int)*2), 0);
		printf("child sender: two numbers  sent: %d byte \n", ret);
		
		
		msg_t2 m3;
		printf("child receiver: waiting for the answer...\n");
		ret = msgrcv(mqid, &m3, sizeof(int), 2, 0);
		printf("child receiver: %d bytes,  received: answer  -- %d\n", ret, m3.z);
	}
	else {
		// parent: receive the message and print it
		msg_t m2;
		printf("  parenrt receiver: waiting  for x and y...\n");
		ret = msgrcv(mqid, &m2, (sizeof(int)*2), 1, 0);
		printf("parent receiver: %d bytes , two numbers recieved: %d  and %d\n", ret, m2.x, m2.y);
		int x=m2.x;
		int y=m2.y;
		int z=x+y;
		
		msg_t2 m4;
		m4.type = 2;
		printf("parent anser sender:\n");
		m4.z=z;
		ret = msgsnd(mqid, &m4,sizeof(int), 0);
		printf("parrent sender: answer sent : %d bytes\n", ret);
	
		// wait for child and clean it up
		wait(&s);

		// destroy the message queue
	//	msgctl(mqid, IPC_RMID, NULL);
	}
	return 0;
}


