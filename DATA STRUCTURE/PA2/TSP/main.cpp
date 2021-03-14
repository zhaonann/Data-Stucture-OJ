//
//  main.cpp
//  PATSP
//
//  Created by nan zhao on 2021/2/9.
//  Copyright © 2021 nan zhao. All rights reserved.
//

#include <iostream>

using namespace std;

//status 0 undiscovered
//       1 visted

struct EdgeNode{
    int data;
//    int status;
    EdgeNode* next;
    EdgeNode(){
        data = 0;
//        status = 0;
        next = NULL;
    }
    EdgeNode(int e, EdgeNode* succ=NULL):data(e),next(succ){}
};

struct Vertex{
    int data;
    int indegree;
    int outdegree;
//    int status;
    int predDist=0;
//    int succDist=0;
    EdgeNode* header;
    Vertex(){
        indegree=0;
        outdegree=0;
//        status=0;
        predDist=0;
//        succDist=0;
        header = new EdgeNode(0);
    }
    Vertex(int e, EdgeNode* f=NULL){
        data=e;
        indegree=0;
        outdegree=0;
//        status=0;
        predDist=1;
//        succDist=0;
        header = new EdgeNode(0);
        
    }
};

class Stack{
private:
    int top;
    int capacity;
    Vertex** S;
public:
    Stack(){
        top=0;
        capacity=20;
    }
    Stack(int cap)
    {
        top=0;
        capacity = cap;
        S = new Vertex*[capacity];
    }
    bool Empty(){
        
        if(top==0)
        {
            return true;
        }else{
            return false;
        }
    }
    void Push(Vertex* v)
    {
        S[top++] = v;
        
    }
    Vertex* Pop()
    {
        return S[--top];
    }
    
};

class Graph{
    
public:
    int Tv; // total number of vertex
    int Te; // total number of edge
    Vertex** V;
    Graph(){}
    Graph(int tv, int te){
        Tv = tv;
        Te = te;
        V = new Vertex*[tv];
        for(int i=1; i<tv+1; i++)
        {
            Vertex* v = new Vertex(i);
            V[i-1]=v;
        }
    }
    void InsertEdge(int a, int b)
    {

        EdgeNode* cur = V[a-1]->header;
        EdgeNode* end = new EdgeNode(b);
        end->next = cur->next; // insert from head
        cur->next = end;
        V[a-1]->outdegree++;
        V[b-1]->indegree++;
    }

 
//    int TSP(){
//
//        int IsoVil = 0;
//        Stack S(Tv);
//        for(int i=0; i<Tv; i++) // precessing
//        {
//            if(V[i]->indegree==0) // backtracking 1.DFS
//            {
//                if(V[i]->outdegree==0)
//                {
//                    IsoVil++;
//                }else{
//                    S.Push(V[i]);
//                }
//            }
//        }
//        int MaxiVil = 0;
//        int clock=0;
//        int bclock=0;
//        int SiMaxVal=0;
//        while(!S.Empty())
//        {
//            clock=1;
//            bclock=0;
//            SiMaxVal=1;
//            TSort(S.Pop(), clock, bclock, SiMaxVal);
//            //Reset();
//            if(SiMaxVal>MaxiVil)
//            {
//                MaxiVil = SiMaxVal;
//            }
//        }
//        if(IsoVil>1)
//        {
//            IsoVil = 1;
//        }
//        return MaxiVil>IsoVil ? MaxiVil:IsoVil;
//    }
    int ToPoTSP(){
        Stack S(Tv);
        for(int i=0; i<Tv; i++) // precessing
        {
            if(V[i]->indegree==0) // backtracking 1.DFS
            {
                S.Push(V[i]);
//                V[i]->predDist = 1;
            }
        }
        int MaxiVil = 1;
        while(!S.Empty())
        {//ref： https://blog.csdn.net/Garrison2012/article/details/50016371
            Vertex* v = S.Pop();
            EdgeNode* e = v->header->next;
            while(e!=NULL){
                Vertex* tmp = V[e->data-1];
//                tmp->status = 1;
                if(tmp->predDist < v->predDist + 1)
                {
                    tmp->predDist = v->predDist + 1;
                }
                
                if(tmp->predDist>MaxiVil)
                {
                    MaxiVil = tmp->predDist;
                }
                
                if(--tmp->indegree==0)
                {
                    S.Push(tmp);
                }

                e=e->next;
            }
        }
        return MaxiVil;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    int n=0, m=0;
    cin>>n>>m;
    Graph G(n,m);
    int a=0,b=0;
    for(int i=0; i<m; i++)
    {
        cin>>a>>b;
        G.InsertEdge(a,b);
    }
    cout<<G.ToPoTSP()<<endl;
    
    return 0;
}

