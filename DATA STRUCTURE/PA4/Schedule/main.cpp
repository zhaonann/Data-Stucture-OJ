//
//  main.cpp
//  Schedule
//
//  Created by nan zhao on 2021/2/16.
//  Copyright © 2021 nan zhao. All rights reserved.
//

//#include <iostream>
#include <cstdio>
#include <string.h>
#include <math.h>
#define N 4000001
#define M 2000001
#define HALFINF 2147483648

//using namespace std;

struct Task{
    unsigned int priority;
    char name[9];
}PQueue[N];
class PriorityQueue{
public:
    int len;
//    Task* PQueue;
    PriorityQueue(int iniCap){
        len=iniCap;
//        PQueue = new Task[len+1];
    }
    void PercolateDown(int rank){
        Task tmp;
        tmp.priority = PQueue[rank].priority;
        strcpy(tmp.name, PQueue[rank].name);
        int s=rank;
        for(int j=s<<1; j<=len; j<<=1){
            if(j<len && !LessThan(PQueue[j],j+1)){
                ++j;
            }
            if(LessThan(tmp,j)) break;
            else{
                PQueue[s].priority = PQueue[j].priority;
                strcpy(PQueue[s].name, PQueue[j].name);
                s=j;
            }
        }
        if(s!=rank){
            PQueue[s].priority = tmp.priority;
            strcpy(PQueue[s].name, tmp.name);
        }
    }
    bool LessThan(Task t, int j){
        if(t.priority<PQueue[j].priority){
            return true;
        }else if(t.priority>PQueue[j].priority){
            return false;
        }else{ // equal priority, judge task's name
            size_t len1 = strlen(t.name);
            size_t len2 = strlen(PQueue[j].name);
            size_t len3 = len1<len2?len1:len2;
            for(int k=0; k<len3; k++){
                if((int)t.name[k]<(int)PQueue[j].name[k]){
                    return true;
                }else if((int)t.name[k]>(int)PQueue[j].name[k]){
                    return false;
                }
            }
            if(len3 == len1){
                return true;
            }else{
                return false;
            }
        }
    }
//    void swap(int i, int j){
//        unsigned int tmp = PQueue[i].priority;
//        char* name = PQueue[i].name;
//        PQueue[i].priority = PQueue[j].priority;
//        strcpy(PQueue[i].name, PQueue[j].name);
//        PQueue[j].priority = tmp;
//        strcpy(PQueue[j].name, name);
//    }
    void Heapify(){
        for(int i=len>>1; i>0; i--){
            PercolateDown(i);
        }
    }
    bool Empty(){
        return 0==len?true:false;
    }
    Task GetMin(){
        return PQueue[1];
    }
    void DelInsert(){
        if(PQueue[1].priority < HALFINF){
            PQueue[1].priority <<= 1;
            PercolateDown(1);
        }else{
            if(len>1){
                //swap(0,len-1);
                PQueue[1].priority = PQueue[len].priority;
                strcpy(PQueue[1].name, PQueue[len].name);
                PercolateDown(1);
            }
            --len;
        }
    }
};
char Out[M][9];
int main(int argc, const char * argv[]) {
    // insert code here...
    int n=0;
    int m=0;
    scanf("%d%d",&n,&m); //https://www.cnblogs.com/Mabinogi/p/5451510.html
    PriorityQueue PQ(n);
    for(int i=1; i<=n; i++){
        scanf("%d",&PQueue[i].priority);
        scanf("%s",PQueue[i].name);
    }
    PQ.Heapify();
    if(m>0){
        unsigned int slot = 0;
        for(int i=0; i<m; i++){
            if(!PQ.Empty()){
                strcpy(Out[i], PQ.GetMin().name);
                PQ.DelInsert();
                ++slot;
            }else{
                break;
            }
        }
        for(int i=0; i<slot; i++){
//            for(auto j=0; j<8; j++)
//            {
//                printf("%d ",Out[i][j]);
//            }
//            printf("\n");
            printf("%s\n",Out[i]);
        }
    }
    return 0;
}
