#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>

char * time_spam;
struct sembuf sem_lock = {0,-1,0}, sem_open = {0,1,0};
int main(){
    
        key_t semkey = ftok("/tmp", 'a');
        int shmid = (shmget(2002, 32, 0666));
        int semid = (semget(semkey, 1, 0666));
        if(semid == -1){
            printf("Sem open err\n");
            exit(0);
        }
        
        if( shmid == -1 ){
            printf("Can't open shared memory\n");
            exit(0);
        }
        
        if((time_spam = shmat( shmid, NULL, 0 )) == (char*)-1){
            printf("Shmat err\n");
            exit(0);
        }
        
        
        
        while(1){
            semop(semid, &sem_lock, 1);
            printf("%s", time_spam);
            semop(semid, &sem_open, 1);
            sleep(1);
        }
        return 0;
    }
