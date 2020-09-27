#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <process.h>

void *send(void *data);

int main( void )
{
	printf("Circular buffer Example\n");

	pthread_t th1;

	pthread_create(&th1, NULL, send, NULL);
	pthread_join(th1, NULL);

	printf("## main terminating...\n");
}

void *send(void *data) {
printf("## consumer terminating...\n");

int serverPID=0, chid=0; 	// Server PID and channel ID

serverPID = getpid(); 		// get server process ID

printf("%i",serverPID);


return NULL;
}
