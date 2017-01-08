#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct quen{
	char pname[8];
	int time1;
	int time2;
	char state;
	struct quen *next;
}QUEN;

struct{
	int id;
	float ArriveTime;
	float RequestTime;
	float StartTime;
	float EndTime;
	float RunTime;
	int status;	/*0-没运行过，1-运行过*/
}arrayTask[4];

typedef struct node{
	char name[20];
	int prio;
	int round;
	int cputime;
	int needtime;
	char state;	/*W-就绪，R-执行，F-完成*/	
	int count;
	struct node *next;
}PCB; 

typedef struct Queue{
	PCB *LinkPCB;	
	int prio;
	int round;
	struct Queue *next;
}ReadyQueue;

float t,d;

void Printresult(int j);
void GetTask();
int fcfs();
void new_n(int s);
void rr();
void feedback();