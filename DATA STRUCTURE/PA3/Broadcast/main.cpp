//
//  main.cpp
//  DownPA3Broadcast
//
//  Created by nan zhao on 2021/2/10.
//  Copyright © 2021 nan zhao. All rights reserved.
//

#include <iostream>

using namespace std;


struct Edge{
    int data;
    Edge* next;
    Edge(){}
    Edge(int e, Edge* n=NULL){
        data = e;
        next = n;
    }
};

//color 0 unstained
//       1 blue FM104.2
//       -1 red  FM98.6
// status 0 unvisited
//        1 visited

struct Vertex{
    int data;
    int status;
    int color;
    int degree;
    Edge* header;
    Vertex(){}
    Vertex(int e){
        data = e;
        status = 0;
        color = 0;
        degree = 0;
    }
    void Init(int e, int c){
        data = e;
        color = c;
        status = 0;
        degree = 0;
        header = new Edge(0);
    }
};

struct QNode{
    int data;
    QNode* pred;
    QNode* succ;
    QNode(){}
    QNode(int e, QNode* p=NULL, QNode* s=NULL){
        data = e;
        pred = p;
        succ = s;
    }
};

class Queue{//two-way queue
public:
    int len;
    QNode* header;
    QNode* tailer;
    Queue(){
        len=0;
        header = new QNode(0);
        tailer = new QNode(0);
        header->succ = tailer;
        tailer->pred = header;
    }
    bool Empty(){
        return len==0?true:false;
    }
    void Enqueue(QNode* v){
        v->pred = tailer->pred;
        v->succ = tailer;
        tailer->pred->succ = v;
        tailer->pred = v;
        len++;
    }
    QNode* Dequeue(){
        QNode* tmp = header->succ;
        header->succ->succ->pred = header;
        header->succ = header->succ->succ;
        tmp->succ = NULL;
        tmp->pred = NULL;
        len--;
        return tmp;
    }
    
};

class Graph{
public:
    int Tv;
    Vertex* V;
    Graph(){}
    Graph(int tv){
        Tv = tv;
        V = new Vertex[Tv];
        for(int i=0; i<Tv; i++){
            V[i].Init(i+1,0);
        }
    }
    void InsertEdge(int a, int b)
    {
        Edge* ea = new Edge(a);
        ea->next = V[b-1].header->next;
        V[b-1].header->next = ea;
        
        Edge* eb = new Edge(b);
        eb->next = V[a-1].header->next;
        V[a-1].header->next = eb;
        
        V[a-1].degree++;
        V[b-1].degree++;
    }
    int BFS(){
        Queue Q;
        QNode* v = new QNode(1);
        V[0].color = 1;
        V[0].status = 1;
        Q.Enqueue(v);
        while(!Q.Empty()){
            QNode* tmp1 = Q.Dequeue();
            Edge* h = V[tmp1->data-1].header->next;
            for(int i=0; i<V[tmp1->data-1].degree; i++){
                QNode* tmp2 = new QNode(h->data);
                if(V[tmp2->data-1].color==0)
                {
                    V[tmp2->data-1].color = -V[tmp1->data-1].color;
                }else if(V[tmp2->data-1].color==V[tmp1->data-1].color){
                    return -1;
                }
                if(V[tmp2->data-1].status==0){
                    V[tmp2->data-1].status=1;
                    Q.Enqueue(tmp2);
                }
                h=h->next;
            }
        }
        return 1;
    }
};
int main(int argc, const char * argv[]) {
    // insert code here...
    int n,m;
    cin>>n>>m;
    int a,b;
    Graph G(n);
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        G.InsertEdge(a, b);
//        if(G.V[a-1].status==0)
//        {
//            G.V[a-1].status = -1;
//        }else if(G.V[a-1].status!=0)
//        {
//            if(G.V[b-1].status==0)
//            {
//                G.V[b-1].status = -G.V[a-1].status;
//            }else if(G.V[a-1].status==G.V[a-1].status){
//                req = -1;
//            }
//        }
    }
    cout<<G.BFS()<<endl;
    return 0;
}
