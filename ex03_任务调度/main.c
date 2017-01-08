# include "public.h"

int main(){
	int i,b,k;
	char a;
	int d[4];
	printf(" \n 1. FCFS\n");
	printf(" 2. RR\n");
	printf(" 3. Feedback Scheduling\n");
	for(i = 0; ; i++){
		printf("Choose what you want to see: ");
		scanf("%d", &a);
		switch(a){

		case 1:
			GetTask();
			printf("The result of fcfs >>>\n");
			printf("TASK\tArrive\tRequest\tStart\tEnd\tCycling\n");
			for(b = 0; b <= 4; b++){
				k = fcfs();
				// k是该次循环中到达时间最小的Task的编号
				d[b] = k;
				// d[]是所有Task的编号；d[b]指的是本次运行的Task的编号
				new_n(k);
			}
			for(b = 0; b <= 4; b++)
				Printresult(d[b]);
			continue;

		case 2:
			rr();
			continue;

		case 3:
			feedback();
			continue;

		default:
			printf("Error input.\n");
		}
	}
	return 0;
}
