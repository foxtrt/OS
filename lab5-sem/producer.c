#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>
struct sembuf sem_lock = {0,-1,0}, sem_open = {0,1,0};
int main(){
	char * time_spam;
    key_t semkey = ftok("/tmp", 'a');
    int shmid = (shmget(2002, 32,IPC_CREAT | 0666));
    int semid = (semget(semkey, 1, IPC_CREAT | 0666 ));
	if (semid == -1){
		printf("Error\n");
		exit(0);
	}
	if (shmid == -1){
		printf("Cant create mem\n");
		exit(0);
	}
if((time_spam = shmat(shmid,NULL,0)) == (char*)-1){
	printf("Error\n");
}
        time_t timer = time(0);
        time_t timing = timer;
        semop(semid, &sem_open, 1);
        while(1){
                timer = time(0);
                if(timer != timing){
                        semop(semid, &sem_lock, 1);
                        sprintf(time_spam, "%s\n", ctime(&timer));
                    
                        semop(semid, &sem_open, 1);
                    sleep(1);
                    
                }
        }
}
