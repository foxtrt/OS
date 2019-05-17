#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>

void* time_now();
pthread_mutex_t mutex;
char * time_spam;


void* time_now(){

	time_t timer;
	struct tm timeval;
	while(1){
        pthread_mutex_lock(&mutex);
			timer = time(0);
			timeval = *localtime(&timer);
			sprintf(time_spam,"%.2d:%.2d:%.2d",timeval.tm_hour,timeval.tm_min,timeval.tm_sec);
        pthread_mutex_unlock(&mutex);
	}
    return 0;
}


int main(){
	pthread_t thread;
	pthread_mutex_init(&mutex,NULL);
	int shm_id;
	key_t semkey = ftok("/tmp", 'a'); 
	shm_id = (shmget(semkey, 2*sizeof(int), IPC_CREAT | 0666));
	if(shm_id == -1){
		printf("Warning\n");
		exit(0);
	}
	if((time_spam = shmat(shm_id,time_spam,0)) == (char*)-1){
	printf("Error\n");
	exit(0);
	}
	pthread_create(&thread,NULL,time_now,NULL);
	sleep(1);
	while(1){
		pthread_mutex_lock(&mutex);
		printf("%s\n",time_spam);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	pthread_mutex_destroy(&mutex);
	return 0;
}
