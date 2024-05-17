#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>


int main(){

int ret,err,s;

ret=fork();
if(ret==0)
{
int fd = open("in.txt", O_RDONLY);
dup2(fd,0);
err=execlp("wc","wc",NULL);
_exit(1);
}
sleep(4);
waitpid(-1,&s,0);
return 0;
}
