/*
	created by premal upadhyay
*/
#include<stdio.h>
#include<conio.h>

struct Process{
	int pNO;
	char name[2];
	int AT;
	int BT;
	int TAT;
	int WT;
	int CT;
};
void fcfsScheduling(struct Process process[], int noProcess);
void sortProcess(struct Process process[], int noProcess);
void dispGranttChart(struct Process process[], int noProcess);
void printTable(struct Process process[], int noProcess);
void average(struct Process process[], int noProcess);
int main(){
	int noProcess;
	int i;
	printf("\nEnter the number of process :- ");
	scanf("%d",&noProcess);
	struct Process process[noProcess];
	printf("\nEnter the process details...");
	for(i = 0 ; i < noProcess ; i++){
		printf("\nProcess name :- ");
		fflush(stdin);
		gets(process[i].name);
		printf("\nProcess arrival time :- ");
		scanf("%d",&process[i].AT);
		printf("\nProcess burst time :- ");
		scanf("%d",&process[i].BT);
		process[i].pNO = i+1;
	}
	fcfsScheduling(process, noProcess);
	printf("\n\nGrantt chart..");
    dispGranttChart(process, noProcess);
    printf("\n\n\n\nProcess table..");
    printTable(process, noProcess);
    average(process, noProcess);
	return 0;

}
void average(struct Process process[], int noProcess){
    double tempTAT;
    for(int i = 0 ; i < noProcess ; i++){
        tempTAT += process[i].TAT;
    }
    double avgTAT = tempTAT/noProcess;
    double tempWT;
    for(int i = 0 ; i < noProcess ; i++){
        tempWT += process[i].WT;
    }
    double avgWT = tempWT/noProcess;
    printf("\n\nAverage turn arround time :- %f",avgTAT);
    printf("\nAverage waiting time :- %f",avgWT);
}
void dispGranttChart(struct Process process[], int noProcess){
    printf("\n");
    printf(" ");
    for(int i = 0 ; i < noProcess ; i++){
        if(process[i].AT != 0 && i==0){
            printf("--");
            printf(" ");
        }
        else if(process[i].AT > process[i-1].CT){
            printf("--");
            printf(" ");
        }

            for(int j = 0 ; j < process[i].BT ; j++)printf("--");
            printf(" ");

    }
	printf("\n|");
	for(int i = 0 ; i < noProcess ; i++){
        if(process[i].AT != 0 && i==0){
            printf("x | ");
        }
        else if(process[i].AT > process[i-1].CT){
            printf("x | ");
        }

             for(int j = 0 ; j < process[i].BT-1 ; j++){
                printf(" ");
            }
            printf("%s",process[i].name);
            for(int j = 0 ; j < process[i].BT-1 ; j++){
                printf(" ");
            }
            printf("|");

	}
	printf("\n");
	for(int i = 0 ; i < noProcess ; i++){
        if(process[i].AT != 0 && i==0){
            printf("--");
            printf(" ");
        }
        else if(process[i].AT > process[i-1].CT){
            printf("--");
            printf(" ");
        }

            for(int j = 0 ; j < process[i].BT ; j++)printf("--");
            printf(" ");

    }
	printf("\n");
	printf("0");

    for(int i=0; i<noProcess; i++) {
        if(process[i].AT != 0 && i == 0){
            printf(" %d",process[i].AT);
        }
        else if(process[i].AT > process[i-1].CT){
        //if(process[i].CT > 9) printf("\b");
            printf(" %d",process[i].AT);
        }
        for(int j=0; j<process[i].BT; j++) printf("  ");
        //if(process[i].CT > 9) printf("\b");
        printf("%d", process[i].CT);
    }
}
void fcfsScheduling(struct Process process[], int noProcess){
	int tct[noProcess];
	sortProcess(process, noProcess);
	int i;
	tct[0] = 0;
	for(i = 0 ; i < noProcess ; i++){
		if(i == 0){
			int diff = process[0].AT - tct[0];
			tct[0] = process[0].BT + diff;
			process[0].CT = tct[0];
			process[0].TAT = process[0].CT - process[0].AT;
            process[0].WT = process[0].TAT - process[0].BT;
		}
		else if(tct[i-1]<process[i].AT){
			int diff = process[i].AT - tct[i-1];
			int temp = tct[i-1] + diff;
			tct[i] = process[i].BT + temp;
			process[i].CT = tct[i];
			process[i].TAT = process[i].CT - process[i].AT;
			process[i].WT = process[i].TAT - process[i].BT;
		}
		else{
            tct[i] = process[i].BT + tct[i-1];
			process[i].CT = tct[i];
			process[i].TAT = process[i].CT - process[i].AT;
			process[i].WT = process[i].TAT - process[i].BT;
		}
	}
}
void printTable(struct Process process[], int noProcess){
    printf("\n");
    printf("\n Process Name.    Arrival Time    Burst Time    Completion Time    Turn Around Time    Waiting Time\n");
	for(int i = 0 ; i < noProcess ; i++){
		int j = 0;
		while(process[j].pNO != (i+1)){
			j = j+1;
		}
		printf("\n\t%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",process[i].name, process[i].AT, process[i].BT, process[i].CT, process[i].TAT, process[i].WT);
	}

}
void sortProcess(struct Process process[], int noProcess){
	struct Process temp;
	int last = noProcess;
	int ex;
	for(int i = 0 ; i < noProcess ; i++){
		ex = 0;
		for(int j = 0 ; j < last ; j++){
			if(process[j].AT > process[j+1].AT){
				temp = process[j];
				process[j] = process[j+1];
				process[j+1] = temp;
				++ex;
			}
		}
		if(ex == 0){
			break;
		}
		else{
			last = last -1;
		}
	}
}
