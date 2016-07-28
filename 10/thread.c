#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m)\
	do \
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)
void * thread_routine(void *arg){
	int i;
	for(i=0;i<20;i++){
		printf("B");
		fflush(stdout);
	}
	return 0;
}
int main(void){
	pthread_t tid;
	int ret;
	if((ret = pthread_create(&tid,NULL,thread_routine,NULL))!=0){
		fprintf(stderr,"pthread_create:%s\n",strerror(ret));
		exit(EXIT_FAILURE);
	}
	int i;
	for( i=0;i<20;i++){
		printf("A");
		fflush(stdout);
	}
	return 0;
}
