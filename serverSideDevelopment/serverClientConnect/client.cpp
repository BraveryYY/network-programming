#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MAXLINE 4096

int main(int argc, char ** argv)
{
	int clientfd;
	struct sockaddr_in servAddr;
	
	if(argc !=2)
	{
		printf("usage:./client <ipaddress>");
		return 0;
	}	
	
	//create socket
	if( (clientfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) ==-1 )
	{
		//create fail
		printf("create error: %s (errno: %d)\n",strerror(errno),errno);
		return 0;
	}
	
	//bind socket
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(6666);
	//bind servaddr's IP
	if(inet_pton(AF_INET,argv[1],&servAddr.sin_addr.s_addr) ==-1)
	{
		//inet_pton error
		printf("inet_pon error: %s(errno: %d)\n",strerror(errno),errno);
		return 0;
	}	
	
	//connect server
	if( connect(clientfd,(struct sockaddr *)&servAddr,sizeof(servAddr) ) == -1)
	{
		//connect error
		printf("connect error: %s (errno: %d)\n",strerror(errno),errno);
		return 0;
	}

	//send msg
	printf("send msg to server!\n");
	char recvline[MAXLINE],sendline[MAXLINE];
	fgets(sendline,4096,stdin);
	if(send(clientfd,sendline,strlen(sendline),0) == -1)
	{
		//send error
		printf("send error: %s (errno: %d)",strerror(errno),errno);
		return 0;
	}
	close(clientfd);
	return 0;

}
