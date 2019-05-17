#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX 10
#define MEMORY 11

int counter = 0;
char * addr;

pthread_rwlock_t rwlock;
void * producer();
void * consumer();

void * producer(){
	while(1){
		if(counter < MAX){
		pthread_rwlock_wrlock(&rwlock);
		addr[counter] = 'T';
		counter++;
		printf("%d - %s\n",counter,addr);
		sleep(1);
		pthread_rwlock_unlock(&rwlock);
	}
}
}


void * consumer(){
	while(1){
		if (counter >= MAX){
			pthread_rwlock_rdlock(&rwlock);
			for(;counter;counter--)
				addr[counter] = ' ';
			printf("Stop\n");
			pthread_rwlock_unlock(&rwlock);
		}
	}
}


int main(){
	void * producer();
	void * consumer();
	pthread_t thread;
	pthread_t consume;
	
	int shm_id;
	if ((shm_id = shmget(2003,MEMORY,IPC_CREAT | 0666)) == -1){
		printf("Warning\n");
		perror(0);
	}
	if ((addr = shmat(shm_id, addr, 0)) == (char *) -1) {
	perror(0);
	}
	pthread_rwlock_init(&rwlock,NULL);
	pthread_create(&thread,NULL,producer,NULL);
	pthread_create(&consume,NULL,consumer,NULL);
	sleep(15);
	pthread_rwlock_destroy(&rwlock);


}
