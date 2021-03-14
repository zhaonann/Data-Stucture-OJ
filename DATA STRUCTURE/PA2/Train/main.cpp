//
//  main.cpp
//  PATrain
//
//  Created by nan zhao on 2021/2/5.
//  Copyright © 2021 nan zhao. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cstring>
class Stack{
    
private:
    int top;
    int* S;
    int capacity;
    
public:
    Stack(){}
    Stack(int cap){
        capacity = cap;
        top=0;
        S = new int[capacity];
    }
    
    bool full()
    {
        return (top==capacity) ? true : false;
    }
    bool empty()
    {
        return (top==0)? true : false;
    }
    
    void push(int e)
    {
        S[top++]=e;
    }
    int pop()
    {
        return S[--top];
   
    }
    int TopElem()
    {
        int Posi = top-1;
        return S[Posi];
    }
    
};

int main(int argc, const char * argv[]) {
    
    int n=0;
    int m=0;
    
    scanf("%d",&n);
    int* Dest = new int[n+1];
    char** oper = new char*[2*n];
    scanf("%d",&m);
    Dest[0]=0;
    for(int i=1; i<n+1;i++)
    {
        scanf("%d", &Dest[i]);
    }
    if(m==0)
    {
        printf("No\n");
        return 0;
    }
    
    Stack TrainS(m);
    
    Stack TrainB(n);
    
    int A=1;
    int e=0;
    int j=0; // track operation
    for(int i=1; i<n+1; i++)
    {
        if(Dest[i]>Dest[i-1]){
            e = A++;

            while(e != Dest[i]){
                if(TrainS.full())
                {
                    printf("No\n");
                    return 0;
                }else{
                    TrainS.push(e);
                    oper[j++]="push";
                }
                e = A++;
                
            }
            if(TrainS.full())
            {
                printf("No\n");
                return 0;
            }else{
                TrainS.push(e);
                oper[j++]="push";
                e = TrainS.pop();
                oper[j++]="pop";
                TrainB.push(e);
            }

        }else{
            
            if(TrainS.empty())
            {
                printf("No\n");
                return 0;
            }else{
                e = TrainS.TopElem();
                if(e!=Dest[i])
                {
                    printf("No\n");
                    return 0;
                }else{
                    e=TrainS.pop();
                    oper[j++] = "pop";
                    TrainB.push(e);
                }
            }
        }
    }
    for(int i=0; i<2*n;i++)
    {
        printf("%s\n",oper[i]);
    }

    return 0;
}
