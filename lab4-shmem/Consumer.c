#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(){
	char * time_spam;//pamyat'
	int shmid;
	key_t semkey = ftok("/tmp", 'a'); 
	shmid = (shmget(semkey, 2*sizeof(int), IPC_CREAT | 0666));
	if(shmid == -1){
		printf("cant open memory\n");
		exit(0);
	}
	if ((time_spam = shmat(shmid,0,0)) == (char*)-1){
		printf("Error\n");
		exit(0);
	}


	while(1){
		printf("%s\n",time_spam);
		sleep(1);
	}
	return 0;
} 