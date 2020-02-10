/*
        created by premal upadhyay
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Process{
        int size;
        char name[2];
        int allocated;
};
struct Block{
        int size;
        char pAllocated[2];
        int isAllocated;
        int bNo;
};
void memoryAllocationFirst(struct Process process[], struct Block blockes[], int noProcess, int noBlock);
void memoryAllocationNext(struct Process process[], struct Block blockes[], int noProcess, int noBlock);
void memoryAllocationBest(struct Process process[], struct Block blockes[], int noProcess, int noBlock);
void memoryAllocationWorst(struct Process process[], struct Block blockes[], int noProcess, int noBlock);
int cmpfunc (const void * a, const void * b);
int main(){
        int i, j, ch;
        int noProcess;
        int noBlock;
        printf("\nEnter the number of process :- ");
        scanf("%d",&noProcess);
        printf("\nEnter the number of block :- ");
        scanf("%d",&noBlock);
        struct Process process[noProcess];
        struct Block blockes[noBlock];
        printf("\nEnter the %d block sizes :- ",noBlock);
        for(i = 0 ; i < noBlock ; i++){
                printf("\nEnter the block %d  sizes :- ",i+1);
                scanf("%d",&blockes[i].size);
                blockes[i].bNo = (i+1);
                blockes[i].isAllocated = 0;
        }
        printf("\nEnter the %d process data :- ",noProcess);
        for(i = 0 ; i < noProcess ; i++){
                printf("\nProcess name :- ");
                fflush(stdin);
                gets(process[i].name);
                printf("\nProcess size :- ");
                scanf("%d",&process[i].size);
                process[i].allocated = 0;
        }
        printf("\n1.First fit algorithm.");
        printf("\n2.Next fit algorithm.");
        printf("\n3.Best fit algorithm.");
        printf("\n4.Worst fit algorithm.");
        printf("\nChoose algorithm for allocation :- ");
        scanf("%d",&ch);
        switch(ch){
          case 1:
            memoryAllocationFirst(process, blockes, noProcess, noBlock);
            break;
          case 2:
            memoryAllocationNext(process, blockes, noProcess, noBlock);
            break;
          case 3:
            memoryAllocationBest(process, blockes, noProcess, noBlock);
            break;
          case 4:
            memoryAllocationWorst(process, blockes, noProcess, noBlock);
            break;
          default:
            printf("\nEnter the valid choice...");
            break;
        }
        return 0;

}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int cmpfunc1 (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}
void memoryAllocationFirst(struct Process process[], struct Block blockes[], int noProcess, int noBlock){
        int internalSum = 0;
        int externalSum = 0;
        int waitProcess = 0;
        int i, j;
        for(i = 0 ; i < noProcess ; i++){
            for(j = 0 ; j < noBlock ; j++){
                if(blockes[j].isAllocated==0 && blockes[j].size >= process[i].size ){
                        strcpy(blockes[j].pAllocated, process[i].name);
                        process[i].allocated = 1;
                        blockes[j].isAllocated = 1;
                        internalSum += (blockes[j].size - process[i].size);
                        break;
                }
            }
        }
        for(i = 0 ; i < noBlock ; i++){
            if(blockes[i].isAllocated == 0){
                    printf("\nProcess is not allocated to this block...");
                    externalSum+=blockes[i].size;
            }
            else{
                    printf("\nBlock %d is allocated to %s process..",i,blockes[i].pAllocated);
            }
        }
        printf("\n\n");
        for(i = 0 ; i < noProcess ; i++){
            if(process[i].allocated == 0){
                printf("\n%s process is waiting..",process[i].name);
                waitProcess += 1;
            }
        }
        printf("\n%d processes are waiting...\n\n",waitProcess);
        printf("\nTotal internal fragmentation :- %d",internalSum);
        printf("\nTotal external fragmentation :- %d",externalSum);
}

void memoryAllocationNext(struct Process process[], struct Block blockes[], int noProcess, int noBlock){
        int internalSum = 0;
        int externalSum = 0;
        int waitProcess = 0;
        int temp = 0;
        int i, j;
        for(i = 0 ; i < noProcess ; i++){
            for(j = temp ; j < noBlock ; j++){
                if(blockes[j].isAllocated==0 && blockes[j].size >= process[i].size ){
                        strcpy(blockes[j].pAllocated, process[i].name);
                        process[i].allocated = 1;
                        blockes[j].isAllocated = 1;
                        internalSum += (blockes[j].size - process[i].size);
                        break;
                }
            }
            temp = j;
        }
        for(i = 0 ; i < noBlock ; i++){
            if(blockes[i].isAllocated == 0){
                    printf("\nProcess is not allocated to this block...");
                    externalSum+=blockes[i].size;
            }
            else{
                    printf("\nBlock %d is allocated to %s process..",i,blockes[i].pAllocated);
            }
        }
        printf("\n\n");
        for(i = 0 ; i < noProcess ; i++){
            if(process[i].allocated == 0){
                printf("\n%s process is waiting..",process[i].name);
                waitProcess += 1;
            }
        }
        printf("\n%d processes are waiting...\n\n",waitProcess);
        printf("\nTotal internal fragmentation :- %d",internalSum);
        printf("\nTotal external fragmentation :- %d",externalSum);
}

void memoryAllocationBest(struct Process process[], struct Block blockes[], int noProcess, int noBlock){
        int internalSum = 0;
        int externalSum = 0;
        int waitProcess = 0;
        int i, j, k = 0;
        int blockNo = 0;
        int diff[100];
        for(i = 0 ; i < noProcess ; i++){
                k = 0;
                blockNo = 0;
            for(j = 0 ; j < noBlock ; j++){
                if(blockes[j].isAllocated==0 && blockes[j].size >= process[i].size){
                    diff[k] = blockes[j].size-process[i].size;
                    ++k;
                }
            }
            qsort(diff, k, sizeof(int), cmpfunc);
            for(int y = 0 ; y < noBlock ; y++){
                if((blockes[y].size-process[i].size)==diff[0]){
                   blockNo = blockes[y].bNo;
                   strcpy(blockes[blockNo-1].pAllocated, process[i].name);
                    process[i].allocated = 1;
                    blockes[blockNo-1].isAllocated = 1;
                    internalSum += diff[0];
                }
            }
        }



        for(i = 0 ; i < noBlock ; i++){
            if(blockes[i].isAllocated == 0){
                    printf("\nProcess is not allocated to this block...");
                    externalSum+=blockes[i].size;
            }
            else{
                    printf("\nBlock %d is allocated to %s process..",i,blockes[i].pAllocated);
            }
        }
        printf("\n\n");
        for(i = 0 ; i < noProcess ; i++){
            if(process[i].allocated == 0){
                printf("\n%s process is waiting..",process[i].name);
                waitProcess += 1;
            }
        }
        printf("\n%d processes are waiting...\n\n",waitProcess);
        printf("\nTotal internal fragmentation :- %d",internalSum);
        printf("\nTotal external fragmentation :- %d",externalSum);
}

void memoryAllocationWorst(struct Process process[], struct Block blockes[], int noProcess, int noBlock){
        int internalSum = 0;
        int externalSum = 0;
        int waitProcess = 0;
        int i, j, k = 0;
        int blockNo = 0;
        int diff[100];
        for(i = 0 ; i < noProcess ; i++){
                k = 0;
                blockNo = 0;
            for(j = 0 ; j < noBlock ; j++){
                if(blockes[j].isAllocated==0 && blockes[j].size >= process[i].size){
                    diff[k] = blockes[j].size-process[i].size;
                    ++k;
                }
            }
            qsort(diff, k, sizeof(int), cmpfunc1);
            for(int y = 0 ; y < noBlock ; y++){
                if((blockes[y].size-process[i].size)==diff[0]){
                   blockNo = blockes[y].bNo;
                   strcpy(blockes[blockNo-1].pAllocated, process[i].name);
                    process[i].allocated = 1;
                    blockes[blockNo-1].isAllocated = 1;
                    internalSum += diff[0];
                }
            }
        }



        for(i = 0 ; i < noBlock ; i++){
            if(blockes[i].isAllocated == 0){
                    printf("\nProcess is not allocated to this block...");
                    externalSum+=blockes[i].size;
            }
            else{
                    printf("\nBlock %d is allocated to %s process..",i,blockes[i].pAllocated);
            }
        }
        printf("\n\n");
        for(i = 0 ; i < noProcess ; i++){
            if(process[i].allocated == 0){
                printf("\n%s process is waiting..",process[i].name);
                waitProcess += 1;
            }
        }
        printf("\n%d processes are waiting...\n\n",waitProcess);
        printf("\nTotal internal fragmentation :- %d",internalSum);
        printf("\nTotal external fragmentation :- %d",externalSum);
}
