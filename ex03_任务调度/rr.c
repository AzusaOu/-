#include "public.h"

void rr(){
	QUEN *q, *p, *head, *m;
	char str[8], f;
	int t, d, n, timeslice = 1;
	printf("Input the max number of TASKs: ");
	scanf("%d",&n);
	d = n;
	if(d>0){
		printf("Input the name of TASK[%d]: ", d);
		scanf("%s",str);
		printf("RequestTime of TASK[%d]: ", d);
		scanf("%d",&t);
		head=p=(QUEN *)malloc(sizeof(QUEN));
		strcpy(p->pname,str);
		p->time1=t;
		p->time2=0;
		p->state='R';
		p->next=NULL;
		head=p;
		getchar();
		--d;
	}
	while(d>0){
		/*构建队列表*/
		printf("Input the name of TASK[%d]: ", d);
		scanf("%s",str);
		printf("RequestTime of TASK[%d]: ", d);
		scanf("%d",&t);
		q=(QUEN *)malloc(sizeof(QUEN));
		strcpy(q->pname,str);
		q->time1=t;
		q->time2=0;
		q->state='R';
		q->next=NULL;
		p->next=q;
		p=q;
		--d;
		p->next=head;
		q=head;
	}
	printf("TASK\tRequest\tRunned\tStatus\n");
	do{
		printf("%s\t%d\t%d\t%c\n",q->pname,q->time1,q->time2,q->state);
		q=q->next;
	}while(q!=head);
	printf("\n");
	do{
		printf("(Timeslice: %d)\n", timeslice);
		if(head->time2<head->time1){
			head->time2++;
			if(head->time2==head->time1){
				head->state='E';
				q=head;
				printf("The running TASK is [%s].\n",q->pname);
				printf("TASK\tRequest\tRunned\tStatus\n");
				do{
					/*输入队列表*/
					printf("%s\t%d\t%d\t%c\n",q->pname,q->time1,q->time2,q->state);
					q=q->next;
				}while(q!=head);
				printf("\n");
				head=head->next;
				q=head;
				p->next=head;
			}
			else{
				printf("The running TASK is [%s].\n",q->pname);
				printf("TASK\tRequest\tRunned\tStatus\n");
				do {
					printf("%s\t%d\t%d\t%c\n",q->pname,q->time1,q->time2,q->state);
					q=q->next;
				}while(q!=head);
				printf("\n");
				head=head->next;
				q=head;
				p=p->next;
			}
			// printf("Is it  needing new process?(y or n)\n");
			// getchar();
			// scanf("%c",&f);
			f = 'n';
			if(f=='Y'||f=='y'){
				getchar();
				printf("Enter the new pname:");
				scanf("%s",str);
				printf("Enter the new neededtime:");
				scanf("%d",&t);
				m=(QUEN *)malloc(sizeof(QUEN));
				strcpy(m->pname,str);
				m->time1=t;
				m->time2=0;
				m->state='R';
				m->next=NULL;
				if(q->next->state=='E'){
					p=m;
					head=m;
					p->next=head;
					q=head;
				}
				else{
					p->next=m;
					m->next=head;
					p=m;
				}
			}
		}
	timeslice++;
	}while(q->next->state!='E');
	printf("All the TASKS are finished!\n");
}