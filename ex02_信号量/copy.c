#include "public.h"   
void copy() {   
    while (1) {   
        sem_wait(&copy_sem);   
        pthread_mutex_lock(&read_mutex);   
        pthread_mutex_lock(&write_mutex);   
        printf("copy running...\n");   
        strcpy(data_t,data_s);   
        int i=0;   
        for(;i<len;i++){   
            data_s[i]=' ';   
        }   
        printf("copy completed.\n");   
        pthread_mutex_unlock(&write_mutex);   
        pthread_mutex_unlock(&read_mutex);   
        sem_post(&write_sem);   
        sem_post(&read_sem);   
        if (result == 0) {   
            result_copy = 1;   
            break;   
        }   
    }   
}


