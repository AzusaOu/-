#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define STRLEN 1024
#define MSGLEN 1024

struct my_msg{ 
	long int mtype;
	char mtext[MSGLEN];
}msg;  

void stop(){}

int pid, p_input, p_distribute;
char getStr[STRLEN], msgtext[MSGLEN];

int main(){

	int shmid1, shmid2, msgid;
	char *addr, *array;
	 
	shmid1 = shmget(IPC_PRIVATE, STRLEN, IPC_CREAT|0777); 
	shmid2 = shmget(IPC_PRIVATE, STRLEN, IPC_CREAT|0777); 
	addr = (char *)shmat(shmid1, NULL, 0); 
	array = (char *)shmat(shmid2, NULL, 0); 
	msgid = msgget(IPC_PRIVATE, IPC_CREAT|0777);  

	pid = getpid();
	while((p_distribute = fork()) == -1); 
	if(p_distribute>0){ 
		while((p_input = fork()) == -1); 
		if(p_input == 0){   
			while(1){
				memset(getStr, '\0', 0); 
				scanf("%s", getStr);
				memset(msg.mtext, '\0', 0);  
				strcpy(msg.mtext, getStr); 
				msg.mtype = 1;
				if(msgsnd(msgid, &msg, MSGLEN, 0)<0)
					return 0;
				if(strcmp(getStr, "quit") == 0)
					break;
			}
			exit(0);
		}
		else{
			printf("Please input a line:\n");
			while(1){ 
				signal(16, stop);
				pause();
				if(strcmp(addr, "quit") == 0){
					printf("Saving...");
					break;
				}
				printf("Your message is:\n%s\n", addr);
				if(strlen(array)!= 0)
					printf("The characters deserted are:\n%s\n", array);  
				memset(addr, '\0', 0); 
				printf("please input a line:\n");
			}
			wait(0);  
			wait(0); 

			shmdt(addr);  
			shmdt(array); 

			shmctl(shmid1, IPC_RMID, 0);  
			shmctl(shmid2, IPC_RMID, 0);  

			msgctl(msgid, IPC_RMID, 0);  
			exit(0); 
		}
	}
	else{
		int i = 0;
		int j = 0;
		FILE *fp1, *fp2;
		fp1 = fopen("letter.txt", "w");
		fp2 = fopen("number.txt", "w");
		while(1){
			if(!msgrcv(msgid, &msg, STRLEN, 0, 0))
				return 0;
			memset(msgtext, '\0', sizeof(msgtext));   
			memset(array, '\0', sizeof(array));   
			strcpy(msgtext, msg.mtext);   
			strcpy(addr, msg.mtext);
			if(strcmp(msgtext, "quit") == 0){
				kill(pid, 16);
				break;   
			}

			for(i=0; i<strlen(msgtext); i++){
				if((msgtext[i] >= 'a'&&msgtext[i] <= 'z')||(msgtext[i] >= 'A'&&msgtext[i] <= 'Z'))   
					fputc(msgtext[i], fp1); 
				else if((msgtext[i] >= '0'&&msgtext[i] <= '9'))   
					fputc(msgtext[i], fp2); 
				else if(msgtext[i] != '\0')
					array[j++] = msgtext[i];
			}
			kill(pid, 16);
		}
		
		fclose(fp1);
		fclose(fp2);
		exit(0);
	}
}