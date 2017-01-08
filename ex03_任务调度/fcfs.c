#include "public.h"

void GetTask(){
	int i;
	float a;
	for(i = 0; i <= 4; i++){
		arrayTask[i].id = i + 1;
		printf("ArriveTime of TASK[%d]: ", i);
		scanf("%f",&a);
		arrayTask[i].ArriveTime = a;
		printf("RequestTime of TASK[%d]: ", i);
		scanf("%f", &a);
		arrayTask[i].RequestTime = a;
		arrayTask[i].StartTime = 0;
		arrayTask[i].EndTime = 0;
		arrayTask[i].RunTime = 0;
		arrayTask[i].status = 0;
	}
}

int fcfs(){
	int i,j,w = 0;
	float t;
	for(i = 0; i <= 4; i++){
		if(arrayTask[i].status == 0){
			t = arrayTask[i].ArriveTime;
			w = 1;
		}
		if(w == 1)
			break;
	}
    /*查找数组中到达时间最小未执行的进程*/
	for(i = 0; i <= 4; i++){
		if(arrayTask[i].ArriveTime < t && arrayTask[i].status == 0)
			t = arrayTask[i].ArriveTime;
	}
    /*返回最小到达时间的数组的下标*/
	for(i = 0; i <= 4; i++){
		if(arrayTask[i].ArriveTime == t)
			return i;
	}
}

/*定义执行进程后相关数据的修改*/
void new_n(int s){
	int i, g = 0;
	for(i = 0; i <= 4; i++){
		if(arrayTask[i].status==0)
			continue;
		else{
			g=1;
			break;
		}
	}
    /*当处理的是第一个未执行的进程时执行*/
	if(g==0){
		arrayTask[s].StartTime=arrayTask[s].ArriveTime;
		arrayTask[s].EndTime=arrayTask[s].RequestTime+arrayTask[s].StartTime;
		arrayTask[s].RunTime=arrayTask[s].RequestTime;
		arrayTask[s].status=1;
		g=1;
	}
    /*当处理的不是第一个未执行的进程时执行*/
	else{
		d = 0;
		/*查找最后执行的进程的完成时间*/
		for(i=0;i<=4;i++){
			if(arrayTask[i].EndTime>d && arrayTask[i].status==1)
				d=arrayTask[i].EndTime;
		}
        /*判断修改的进程的到达时间是否在前一个执行的进程的完成时间前面*/
		if(arrayTask[s].ArriveTime<d)
			arrayTask[s].StartTime=d;
		else
			arrayTask[s].StartTime=arrayTask[s].ArriveTime;
		arrayTask[s].EndTime=arrayTask[s].StartTime+arrayTask[s].RequestTime;
		arrayTask[s].RunTime=arrayTask[s].EndTime-arrayTask[s].ArriveTime;
		arrayTask[s].status=1;
	}
}

void Printresult(int j){
	printf("%d\t",arrayTask[j].id);
	printf("%5.2f\t",arrayTask[j].ArriveTime);
	printf("%5.2f\t",arrayTask[j].RequestTime);
	printf("%5.2f\t",arrayTask[j].StartTime);
	printf("%5.2f\t",arrayTask[j].EndTime);
	printf("%5.2f\n",arrayTask[j].RunTime);
}

