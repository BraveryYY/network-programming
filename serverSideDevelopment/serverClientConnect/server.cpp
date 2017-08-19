#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define MAXLINE 4096

int main()
{
	int listenfd;
	struct sockaddr_in servaddr;
	//create socket
	if( (listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) ==-1 )
	{
		printf("create socket error: %s(errno:%d)\n",strerror(errno),errno);
		return 0;
	}

	//bind socket
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
	{
		printf("bind socket error:%s(errno:%d)\n",strerror(errno),errno);
		return 0;
	}

	//listen 
	if( listen(listenfd,10) == -1)
	{
		printf("listen socket error: %s (errno: %d)",strerror(errno),errno);
	}
	
	//accept
	while(1)
	{
		char buff[MAXLINE];
		int connectfd;
		struct sockaddr_in clientAddr;
		if( (connectfd = accept(listenfd,(struct sockaddr*)NULL,NULL )== -1))
		{
			printf("accept socket error: %s (errno:%d)",strerror(errno),errno);
			continue;
		}
		else
		{
			//print the client's addr and port
			int clientPort;
			int clientIPAddr;
			//clientPort = ntohs(clientAddr.sin_port);//?
			//clientIPAddr = ntohs(clientAddr.sin_addr.s_addr);
			//printf("connect client IP & Port: %d:%d",clientIPAddr,clientPort);
			int ret = recv(connectfd,buff,MAXLINE,0);
			buff[ret] = '\0';
			printf("get massage form client: %s",buff);
			close(connectfd);
		}
	}
	close(listenfd);
	return 0;
}
