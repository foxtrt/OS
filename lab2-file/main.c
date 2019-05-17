#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


#define FILE_SIZE 314572800
#define BLOCK_SIZE 1024
#define SOURCE "source.txt"
#define TARGET "target.txt"


void generate();
void move();

int main (int argc, char * argv[]) {
    pid_t pid;
    if ((pid = fork())) {
        generate();
    } else {
        sleep(1);
        move();
    }
}

void generate(){
	int fd;
	char * buffer = (char *)calloc(BLOCK_SIZE,sizeof(char));
	if ((fd = open(SOURCE,O_WRONLY | O_TRUNC | O_CREAT, S_IWRITE|S_IREAD)) ==  -1){
		perror("cant open file");
		exit(0);
	}
		for (int i=0;i<FILE_SIZE / BLOCK_SIZE;i++){
		write(fd,buffer,BLOCK_SIZE);
	}
	close(fd);
	printf("File generated\n");
}


void move (){
	int readfd = open(SOURCE, O_RDONLY);
	int writefd = open(TARGET, O_WRONLY | O_TRUNC | O_CREAT, S_IWRITE|S_IREAD);

	if(writefd<0){
		printf("Can't open file\n");
		exit(0);
	}
	if(readfd<0){
                printf("Can't open file\n");
                exit(0);
        }

	char * buff = (char*)calloc(FILE_SIZE, sizeof(char));
	

	int i=0;
	ssize_t buf_amount;

	buf_amount = read(readfd, buff, FILE_SIZE);
	do{
		i++;
		write(writefd, buff, buf_amount);
		buf_amount = read(readfd, buff, FILE_SIZE);
	}while(buf_amount);
	


	close(readfd);
	close(writefd);
	printf("File %s copied\n", SOURCE);
}

