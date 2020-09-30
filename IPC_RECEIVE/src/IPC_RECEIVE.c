#include "IPC.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <process.h>




int main( void )
{
	pthread_t th1;
	pthread_create(&th1,NULL, Client , NULL);
	pthread_join(th1, NULL);
	printf("## main terminating...\n");
}


