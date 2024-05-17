#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
// create child process
//send two numbers from child via pipe
//calculate the sum of numbers received form pipe i.e. child
//create anothe pipe and send the resul of additoin from parretn to 
//child via that another pip

int ret,val,s;
int arr1[2],arr2[2];

ret=pipe(arr1);
if(ret<0)
{
perror("pipe failed");
_exit(0);
}

ret=pipe(arr2);
if(ret<0)
{
perror("pipe failed");
_exit(0);
}

val=fork();
if(val==0)
{
close(arr1[0]);
printf("child process::\n");
int x,v;
printf("enter first number\n");
scanf("%d",&x);
write(arr1[1],&x,4);
printf("enter second number\n");
scanf("%d",&x);
write(arr1[1],&x,4);
close(arr1[1]);
close(arr2[1]);
read(arr2[0],&v,4);
printf("answer form %d\n",v);
close(arr2[0]);
}
else
{
printf("at parrent::\n");
close(arr1[1]);
int y,z,r;
read(arr1[0],&y,4);
printf("num1=%d\n",y);
read(arr1[0],&z,4);
printf("num2=%d\n",z);
close(arr1[0]);
r=y+z;
close(arr2[0]);
write(arr2[1],&r,4);
close(arr2[1]);
waitpid(-1,&s,0);
}
return 0;
}
