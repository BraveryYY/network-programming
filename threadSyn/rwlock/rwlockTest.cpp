#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define THREADNUM 5
pthread_rwlock_t rwlock;

void *readers(void *arg)
{	
	pthread_rwlock_rdlock(&rwlock);
	printf("reader %ld got the lock\n",(long)arg);
	pthread_rwlock_unlock(&rwlock);
	pthread_exit((void *) 0);
}

void *writers(void * arg)
{
	pthread_rwlock_wrlock(&rwlock);
	printf("writer %ld got the lock\n",(long) arg);
	pthread_rwlock_unlock(&rwlock);
	pthread_exit((void *) 0);
}

int main()
{
	int iRet;
	iRet = pthread_rwlock_init(&rwlock, NULL);
	if(iRet)
	{
		printf("rwlock initialed failed...");
		//fprintf(stderr,"init lock failed");
		return iRet;
	}
	pthread_t writer_id,reader_id;
	pthread_attr_t attr;
	//this are two ways to change the thread the state of detache or joinable.way one could set in befor .way two detach after thread created.
	//way one:set the parameter of attr.this parameter attr is function pthread_create's second parameter.
	//	  pthread_attr_t attr
	//	  pthread_attr_init(&attr);
	//	  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED)
	//way two:use the function pthread_detach(pthread_t pid)
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
	//create thread
	int nreadercount = 1;
	int nwritercount = 1;
	for(int i = 0; i< THREADNUM; ++i)
	{
		if(i%3)
		{	
			pthread_create(&reader_id, &attr,readers,(void *)nreadercount);
			printf("create reader %d\n",nreadercount++);
		}
		else
		{
			pthread_create(&writer_id,&attr,writers,(void *)nwritercount);
			printf("create writer %d\n",nwritercount++);
		}
	}	
	sleep(5);
	return 0;
}
