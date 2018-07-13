#include "apue.h"
#include <unistd.h>
#include <pthread.h>

char buf[] = "abcedfghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n";

void *print_fn(void *args) {
	for (int i = 0; i < 100; i ++)
    printf("%s", buf);
	return NULL;
}

void *write_fn(void *args) {
	for (int i = 0; i < 100; i ++)
    write(STDOUT_FILENO, buf, strlen(buf));
	return NULL;
}

void *pwrite_fn(void *args) {
	for (int i = 0; i < 100; i ++)
    pwrite(STDOUT_FILENO, buf, strlen(buf), SEEK_END);
	return NULL;
}

void f_t(void * (*f)(void *)) {
  pthread_t t1, t2;
	pthread_create(&t1, NULL, f, NULL);
	pthread_create(&t2, NULL, f, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

void f_p(void * (*f)(void *)) {
  fork();
	(*f)(NULL);
}

int main(void) {
  // Parallel execution of printf in processes.
	f_p(&print_fn);
	
	// Parallel execution of printf in threads.
	// f_t(&print_fn);
	
	// Parallel execution of write in processes.
	// f_p(&write_fn);
	
	// Parallel execution of pwrite in threads.
	// f_t(&write_fn);
	
  exit(0);
}
