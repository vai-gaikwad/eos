#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

int arr[2];

void sig_handler(int sig)
{
 close(arr[0]);
 close(arr[1]);
// printf("count = %d\n",cnt);
 _exit(0);
}

int main()
{
int ret;
double cn;
char ch='A';
struct sigaction sa;
sa.sa_handler=sig_handler;
ret=sigaction(SIGTERM,&sa,NULL);
if(ret<0)
{
perror("sigaction failed");
_exit(0);
}

ret=pipe(arr);
while(1)
{
cn++;
write(arr[1],&ch,1);
printf("%f\n",cn);
}

return 0;
}
