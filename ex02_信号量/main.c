#include "public.h"

void file_in(int fd, char *data, int len) {   
    while (1) {   
        sem_wait(&read_sem);   
        pthread_mutex_lock(&read_mutex);   
        printf("F_in running...\n");   
        if (lseek(fd, 0, SEEK_CUR) == -1) {   
            printf("lseek failed!\n");   
        }   
        if ((result = read(fd, data, len)) == -1) {   
            printf("read failed! \n");   
        }   
        int i=0,j=0;   
        printf("F_in completed.\n");   
        pthread_mutex_unlock(&read_mutex);   
        sem_post(&copy_sem);   
        if(result<len){   
            len=result;   
            result=0;   
            break;   
        }   
    }   
}

void file_out(int fd, char *data, int len) {   
    while (1) {   
        sem_wait(&write_sem);   
        pthread_mutex_lock(&write_mutex);   
        printf("F_out running...\n");   
        if (write(fd, data, len) == -1) {   
            printf("write failed! \n");   
        }   
        printf("F_out completed.\n");   
        pthread_mutex_unlock(&write_mutex);   
        if(result_copy==1){   
            break;   
        }   
    }   
}

int isdigit_all(char *str)    
{    
	while (*str != '\0')    
	{    
		if (!isdigit(*str++))    
			 return 0;    
	}    
	return 1;    
}    
    
void Handlesignal(int signo) {    
	printf("Finished.\n", signo);    
	exit(0);    
}    

void main(int argc, char* argv[]) {    
	if(argc!=4){
		printf("Proper format: SIGNAL [F_in] [F_out] [buffer length]\n");
		exit(0);
	}    
	if(isdigit_all(argv[3])==0){    
		printf("Length of buffer must be digit!\n");    
		exit(0);    
	}
	result_copy = 0;    
	filename_in=argv[1];    
	filename_out=argv[2];    
	len=atoi(argv[3]);    
	int thread_i = 0;    
	data_s = (char *) malloc(len * sizeof(char));    
	data_t = (char *) malloc(len * sizeof(char));    
    
	if (signal(SIGINT, Handlesignal) == SIG_ERR) {	
		printf("error signal out\n");    
	}    
	pthread_t read_pthread;    
	pthread_t copy_pthread;    
	pthread_t write_pthread;    
    
	int ini1 = sem_init(&read_sem, 0, 1);    
	int ini2 = sem_init(&write_sem, 0, 0);    
	int ini5 = sem_init(&copy_sem, 0, 0);    
	if (ini1 && ini2 && ini5 != 0) {    
		printf("sem error\n");
		exit(1);    
	}    

	int ini3 = pthread_mutex_init(&read_mutex, NULL);    
	int ini4 = pthread_mutex_init(&write_mutex, NULL);    
	if (ini3 && ini4 != 0) {    
		printf("mutex error\n");    
		exit(1);    
	}    
	int thread_1 = pthread_create(&read_pthread, NULL, (void *)&get,    
			 (void *) (&thread_i));    
	if (thread_1 != 0) {    
		printf("read thread create error!\n");    
		exit(1);    
	}    
	thread_i++;    
	int thread_2 = pthread_create(&copy_pthread, NULL, (void *)&copy,    
			 (void *) (&thread_i));    
	if (thread_2 != 0) {    
		printf("copy thread create error!\n");    
		exit(1);    
	}    
	thread_i++;    
	int thread_3 = pthread_create(&write_pthread, NULL, (void *)&put,    
			 (void *) (&thread_i));    
	if (thread_3 != 0) {    
		printf("write thread create error!\n");    
		exit(1);    
	}    
	pthread_join(read_pthread, NULL);    
	pthread_join(copy_pthread, NULL);    
	pthread_join(write_pthread, NULL);    
	free(data_s);    
	free(data_t);    
	exit(0);    
}    
    

