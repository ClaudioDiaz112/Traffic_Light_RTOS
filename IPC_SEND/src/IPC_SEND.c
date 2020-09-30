#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include "IPC.h"
void* Test(void);
int main( void )
{
	pthread_t th1,th2;
	pthread_create(&th1, NULL, Server, NULL);
	pthread_create(&th2, NULL, Test, NULL);

	pthread_join(th2, NULL);
	printf("## main terminating...\n");
}

void* Test(void){
	while(1){
	printf("test to see what is blocked\n");
	sleep(1);
	}
}



