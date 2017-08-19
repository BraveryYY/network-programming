#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdlib.h>

#define CUSTOMER_NUM 10

sem_t sem;

void* get_service(void* thread_id)
{
	int customer_id = *((int *)thread_id);
	if(sem_wait(&sem) == 0)
	{
		usleep(100);//service time:100ms
		printf("customer %d receive service...\n",customer_id);
		sem_post(&sem);
	}
}

int main()
{	
	//int sem_init(sem_t *sem, int pshared, unsigned int value);
	//sem:initialed semaphore
	//pshared: if pshared == 0 -> local semaphore in current process
	//         if pshared !=0 -> shared by multi process
	//value:sem's initial value. in this example: represent the count could be servered in the same time.
	sem_init(&sem,0,2);
	pthread_t customers[CUSTOMER_NUM];
	
	int iret;//create thread return value
	for(int i = 0;i< CUSTOMER_NUM;++i)
	{
		int customer_id = i;
		int iret = pthread_create(&customers[i],NULL,get_service,&customer_id);
		if(iret)
		{
			printf("create thread %d failed...",customer_id);
			return iret;
		}
		else
		{
			printf("created %d thread...",customer_id);
		}
		usleep(10);
	}
	
	//wait created thread exit
	//here can't use the local int i,becauce thread customer[i] is being used	
	for(int j = 0; j< CUSTOMER_NUM; ++j)
	{
		//second parameter represent the child thread returned value.
		pthread_join(customers[j],NULL);
	}
	//destroy semaphore
	sem_destroy(&sem);
	return 0;
}	
