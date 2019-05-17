#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
																																				
char * time_spam;
void time_now();

int main(){
	int shmid;
	key_t semkey = ftok("/tmp", 'a'); 
	shmid = (shmget(semkey, 2*sizeof(int), IPC_CREAT | 0666));
	if (shmid == -1){
		printf("cant open memory\n");
		exit(0);
	}

	if ((time_spam = shmat(shmid,time_spam,0)) == (char *)-1){
		printf("Error\n");
		exit(0);
	}

	time_now();


}
void time_now(){
	struct tm timeval;
	while(1){
		time_t timer = time(0);
		timeval = *localtime(&timer);
		 sprintf(time_spam, "%.2d:%.2d:%.2d", timeval.tm_hour, timeval.tm_min, timeval.tm_sec);
		 sleep(1);

	}
}