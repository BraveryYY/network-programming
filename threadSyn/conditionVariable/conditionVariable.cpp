#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<iostream>

using namespace std;

int travalerCount = 0;

//condition variable
pthread_cond_t taxiCond = PTHREAD_COND_INITIALIZER;
//mutex
pthread_mutex_t taxiMutex = PTHREAD_MUTEX_INITIALIZER;

void * traveler_arrive(void * name)
{
	cout << "Traveler: " << (char *)name << " needs a taxi now!" << endl;
	pthread_mutex_lock(&taxiMutex);
	travalerCount++;
	pthread_cond_wait(&taxiCond,&taxiMutex);
	//cout << "hahah "<<endl;
	pthread_mutex_unlock(&taxiMutex);
	cout << "Traveler: "<<(char *)name<<" now got a taxi!"<<endl;
	pthread_exit((void *) 0);
}

void * taxi_arrive(void * name)
{
	cout << "Taxi"<< (char *)name<<" arrives."<<endl;
	while(1)
	{

		pthread_mutex_lock(&taxiMutex);
		if(travalerCount>0)
		{
			pthread_cond_signal(&taxiCond);
			//travalerCount--;
			pthread_mutex_unlock(&taxiMutex);
			break;
		}	
		pthread_mutex_unlock(&taxiMutex);
	}
	pthread_exit((void *)0);
}

int main()
{
	pthread_t tids[3];
	int iRet = pthread_create(&tids[0],NULL,taxi_arrive,(void *)(" jack"));
	if(iRet)	
	{
		printf("pthread_create error: iRet = %d\n",iRet);
		return iRet;
	}
	cout << "Time passing by."<<endl;
	sleep(1);
	
	iRet = pthread_create(&tids[1],NULL,traveler_arrive,(void *)(" susan"));
	if(iRet)	
	{
		printf("pthread_create error: iRet = %d\n",iRet);
		return iRet;
	}
	
	cout << "Time passing by."<<endl;
	sleep(1);
	
	iRet = pthread_create(&tids[2],NULL,taxi_arrive,(void *)(" Mike"));
	if(iRet)	
	{
		printf("pthread_create error: iRet = %d\n",iRet);
		return iRet;
	}
	
	cout << "Time passing by"<<endl;
	sleep(1);
	void * retval;
	for(int i = 0;i<3;++i)
	{
		iRet = pthread_join(tids[i],&retval);
		if(iRet)
		{
			printf("pthread_join error: iRet = %d\n",iRet);
			return iRet;
		}
		printf("retval = %d\n",retval);
	}
	//cout << "iRet num : "<<strerror(errno)<<"errno: "<<iRet<<endl;	
	return 0;

}
