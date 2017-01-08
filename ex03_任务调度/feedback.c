# include "public.h"

PCB *run=NULL,*finish=NULL;
ReadyQueue *Head = NULL;
int num;
int ReadyNum;

void Output(){
	ReadyQueue *print = Head; 
	PCB *p; 
	printf("TASK\tPrio\tRound\tCPUTime\tRequest\tStatus\tCount\n"); 
	while(print){	 
		if(print ->LinkPCB != NULL){	 
			p=print ->LinkPCB; 
			while(p){	 
				printf("%s\t%d\t%d\t%d\t%d\t%c\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);		
				p = p->next; 
			}
		}	 
		print = print->next; 
	}	 
	p = finish; 
	while(p!=NULL){	 
		printf("%s\t%d\t%d\t%d\t%d\t%c\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count); 
		p = p->next; 
	}	 
	p = run; 
	while(p!=NULL){	 
		printf("%s\t%d\t%d\t%d\t%d\t%c\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count); 
		p = p->next; 
	}
}

void InsertFinish(PCB *in){	 
	PCB *fst;
	fst = finish;
	if(finish == NULL){	 
		in->next = finish; 
		finish = in; 
	}
	else{	 
		while(fst->next != NULL)	 
			fst = fst->next; 
		in ->next = fst ->next; 
		fst ->next = in; 
	}
}

void InsertPrio(ReadyQueue *in){	 
	ReadyQueue *fst,*nxt;
	fst = nxt = Head;
	if(Head == NULL){	 
		in->next = Head; 
		Head = in; 
	}	 
	else{	 
		if(in ->prio >= fst ->prio){	 
			in->next = Head; 
			Head = in; 
		}	 
		else{	 
			while(fst->next != NULL){
				nxt = fst; 
				fst = fst->next; 
			}
			if(fst ->next == NULL){	 
				in ->next = fst ->next; 
				fst ->next = in; 
			}
			else{	 
				nxt = in; 
				in ->next = fst;
			}
		}
	}
}

void PrioCreate(){	 
	ReadyQueue *tmp; 
	int i; 
	printf("Number of priority queue: "); 
	scanf("%d",&ReadyNum); 
	printf("Timeslice for each queue:\n"); 
	for(i = 0;i < ReadyNum; i++){	 
		if((tmp = (ReadyQueue *)malloc(sizeof(ReadyQueue)))==NULL){	 
			perror("malloc"); 
			exit(1); 
		}
		scanf("%d",&(tmp->round)); /*输入此就绪队列中给每个进程所分配的CPU时间片*/
		tmp ->prio = 50 - tmp->round; /*设置其优先级，时间片越高，其优先级越低*/
		tmp ->LinkPCB = NULL; /*初始化其连接的进程队列为空*/
		tmp ->next = NULL; 
		InsertPrio(tmp); /*按照优先级从高到低，建立多个就绪队列*/
	}
}

void GetFirst(ReadyQueue *queue){	 
	run = queue ->LinkPCB;
	if(queue ->LinkPCB != NULL){	 
		run ->state = 'R'; 
		queue ->LinkPCB = queue ->LinkPCB ->next; 
		run ->next = NULL; 
	}
}

void InsertLast(PCB *in,ReadyQueue *queue){	 
	PCB *fst; 
	fst = queue->LinkPCB; 
	if( queue->LinkPCB == NULL){	 
		in->next =	queue->LinkPCB; 
		queue->LinkPCB = in; 
	}	 
	else{
		while(fst->next != NULL) 
			fst = fst->next;  
		in ->next = fst ->next; 
		fst ->next = in; 
	}
}

void ProcessCreate(){	 
	PCB *tmp; 
	int i; 	
	printf("Number of TASKs: "); 
	scanf("%d",&num); 
	printf("Each TASK's name and request time:\n"); 
	for(i = 0;i < num; i++){	 
		if((tmp = (PCB *)malloc(sizeof(PCB)))==NULL){	 
			perror("malloc"); 
			exit(1); 
		}	 
		scanf("%s",tmp->name);getchar();
		scanf("%d",&(tmp->needtime)); 
		tmp ->cputime = 0; 
		tmp ->state ='W'; 
		tmp ->prio = 50 - tmp->needtime;
		tmp ->round = Head ->round; 
		tmp ->count = 0; 
		InsertLast(tmp,Head);
	}
}

void RoundRun(ReadyQueue *timechip){
	int flag = 1; 	
	GetFirst(timechip); 
	while(run != NULL){	 
		while(flag){	 
			run->count++; 
			run->cputime++; 
			run->needtime--; 
			if(run->needtime == 0){	 
			run ->state = 'F';	// End
			InsertFinish(run); 
			flag = 0; 
			}	 
			else if(run->count == timechip ->round){	 
				run->state = 'W';	// Time out 
				run->count = 0;
				InsertLast(run,timechip); 
				flag = 0;
			}	 
		}	 
		flag = 1; 
		GetFirst(timechip);
	}	 
}

void MultiDispatch(){
	int flag = 1; 
	int k = 0; 
	ReadyQueue *point; 
	point = Head; 
	GetFirst(point); 
	while(run != NULL){	 
		Output(); 
		if(Head ->LinkPCB!=NULL) 
			point = Head; 
			while(flag){
				run->count++; 
				run->cputime++; 
				run->needtime--; 
				if(run->needtime == 0){
					run ->state = 'F'; 
					InsertFinish(run); 
					flag = 0;
				}
				else if(run->count == run->round){
					run->state = 'W';
					run->count = 0;
					if(point ->next!=NULL){
					run ->round = point->next ->round;
					InsertLast(run,point->next);
					flag = 0; 
				}
				else{
					RoundRun(point);
					break; 
				}	 
			}	 
			++k;
		}	 
		flag = 1; 
		if(point ->LinkPCB == NULL)
		point =point->next; 
		if(point ->next ==NULL){	 
			RoundRun(point); 
			break; 
		}
		GetFirst(point); 
	}	 
}

void feedback(){	 
	PrioCreate();
	ProcessCreate();
	MultiDispatch();
	Output();
}