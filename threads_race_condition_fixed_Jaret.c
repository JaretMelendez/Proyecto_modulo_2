/* 	Description: 	Creating threads and using them through an increment loop
	Creation date:	September 15, 2022
	Code creator: 	Jaret Mohamet Melendez Perez	*/

// ----- Libraries -----
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// ----- Declaration of the mutex variable and its respective initialization -----
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// ----- Global variable -----
int x = 0;

void* thread_func(void* args){

    int i;
    for ( i = 0; i < 10000000; i++ )
    {
        pthread_mutex_lock(&mutex);//-> Allows to request access to the mutex, the thread blocks until it is obtained
		x++; // errata from the processes class: this is not atomic
		pthread_mutex_unlock(&mutex);//-> Allow free mutex
    }
}

// ----- Principal Function -----
int main () {
    pthread_t thread_id[2];
// ----- Shows in terminal initial state of the variable "x" -----
    printf("I will create two threads\n");
    printf("Point 1 >> X is: %d\n", x);
// ----- Thread creation -----
	pthread_create(&thread_id[0],NULL,&thread_func,NULL);
    pthread_create(&thread_id[1],NULL,&thread_func,NULL);
    printf("The threads has been created\n");
// ----- Wait for the threads to finish -----
	pthread_join(thread_id[0],NULL);
    pthread_join(thread_id[1],NULL);
// ----- shows in terminal the final state of the variable "x" -----
    printf("The threads have exited\n");
    printf("Point 2 >> X is: %d\n", x);

    return 0;
}
/* 	What was done to fix the race problem was to use the "mutex", which is set or blocked before the global variable
	is incremented and released after the global variable performs the assigned increment.*/