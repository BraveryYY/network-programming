#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<stdlib.h>

#define MAXFILE 65535

int main()
{
	pid_t pc;
	//first step:create child process
	pc = fork();
	if(pc<0)
	{
		printf("error fork\n");
		exit(1);
	}
	else if( pc >0)
	{
		exit(0);
	}
	// pc == 0 is the child process
	//second step:setsid()
	setsid();
	//third step:change pwd
	chdir("/");
	//forth step:umask()
	umask(0);
	//fifth step:close file resources
	for(int i = 0;i< MAXFILE;++i)
	{
		close(i);
	}

	char *buf = "this is a daemon\n";
	int bufLen = sizeof(buf);
	int fd;
	while(1)
	{
		if(( fd = open("/tmp/daemon.log",O_CREAT|O_WRONLY|O_APPEND,0600) )<0)
		{
			perror("open");
			exit(1);
		}
		write(fd,buf,bufLen);
		close(fd);	
		sleep(10);
	}
	return 0;
}
