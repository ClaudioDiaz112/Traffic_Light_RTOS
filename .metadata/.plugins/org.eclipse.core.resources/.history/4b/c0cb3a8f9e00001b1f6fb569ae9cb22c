#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *receive(void) {
printf("## receive terminating...\n");



}
void main( void )
{
	printf("Circular buffer Example\n");

	pthread_t th1;

	pthread_create(&th1, NULL, receive, NULL);
	pthread_join(th1, NULL);

	printf("## main terminating...\n");
}

