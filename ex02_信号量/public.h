#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
sem_t read_sem;
sem_t write_sem;
sem_t copy_sem;

pthread_mutex_t read_mutex;
pthread_mutex_t write_mutex;

char *data_s;
char *data_t;
int len;

char *filename_out;
char *filename_in;

int result;
int result_copy;

void copy();
void put();
void get();
