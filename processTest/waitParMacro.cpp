#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid<0)
	{
		perror("fork error\n");
		exit(1);
	}
	else if(pid>0)
	{
		//parent process
		int retStatus = -1;
		printf("parent process!\n");
		pid_t pr = wait(&retStatus);
		if(WIFEXITED(retStatus))
		{
			printf("the child process %d exit normally.\n",pr);
			printf("the child process return value retStatus: %d\n",WEXITSTATUS(retStatus));
		}
		else
		{
			printf("the child process %d exit abnormally.\n",pr);
		}
	}
	else
	{
		//child process
		printf ("sub-process, PID: %u, PPID: %u\n",getpid(),getppid());
		exit(3);
	}
	return 0;
}
