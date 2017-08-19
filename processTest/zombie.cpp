#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{	
	//for a child process
	pid_t pid = fork();
	if(pid < 0)
	{
		printf("fork error\n");
		exit(1);
	}
	else if( pid >0)
	{
		//parent process
		printf("in parent process, sleep for one miniute...zZ...\n");
		sleep(5);
		printf("after sleeping ,and exit\n");
	}
	else
	{
		//child process  --->zombie
		printf("in child process , and exit\n");
		exit(0);
	}
	return 0;
}
