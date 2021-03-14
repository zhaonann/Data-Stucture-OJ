//
//  main.cpp
//  PAProperRebuild
//
//  Created by nan zhao on 2021/2/6.
//  Copyright © 2021 nan zhao. All rights reserved.
//

#include <iostream>

using namespace std;

int m=0;

struct Node{
    int data;
    Node* left;
    Node* right;
    
    Node(){}
    Node(int e, Node* l=NULL, Node* r=NULL):data(e),left(l),right(r){}
    
};
class Stack{
private:
    int top;
    Node** vec;
    int capacity;
public:
    Stack(){
        top=0;
        capacity = 20;
        vec = new Node*[capacity];
    }
    Stack(int cap){
        top=0;
        capacity=cap;
        vec = new Node*[capacity];
    }
    bool empty(){
        return (top==0)?true:false;
    }
    bool full()
    {
        return (top==capacity)?true:false;
    }
    void push(Node* e)
    {
        vec[top++]=e;
    }
    Node* pop(){
        return vec[--top];
    }
    Node* TopElem(){
        int posi = top-1;
        return vec[posi];
    }
};
class Tree{
public:
    Node* root;
    int _size;
public:
    Tree()
    {
        root = NULL;
        _size=0;
    }
    Tree(Node* r, int n){
        root=r;
        _size=n;
    }
    
    
//    void InsertAsLeft(Node* posi, int e){
//        Node* l = new Node(e);
//        posi->left = l;
//        _size++;
//    }
//    void InsertAsRight(Node* posi, int e){
//        Node* r = new Node(e);
//        posi->right = r;
//        _size++;
//    }
    void Visit(Node* n)
    {
        cout<<n->data<<" ";
    }
    void InorderRec(Node* r) // recursive version
    {
        if(!r){
            return;
        }else
        {
            InorderRec(r->left);
            Visit(r);
            InorderRec(r->right);
        }
    }
    
    void PreorderRec(Node* r) // recursive version
    {
        if(!r){
            return;
        }else
        {
            Visit(r);
            InorderRec(r->left);
            InorderRec(r->right);
        }
    }
    
    void GoAlongLeftmost(Node* n, Stack& S)
    {
        while(n!=NULL){
            Visit(n);
            if(n->right!=NULL)
            {
                S.push(n->right);
            }
            n = n->left;
        }
    }
    void PreorderIte(Node* r) // iteration scheme p127
    {
        Stack S(_size);
        GoAlongLeftmost(r, S);
        while(!S.empty())
        {
            Node* c=S.pop();
            GoAlongLeftmost(c,S);
        }
        
    }
    
    void GoAlongLeftBranch(Node *n, Stack& S)
    {
        while(n)
        {
            S.push(n);
            n=n->left;
        }
    }
    
    void InorderIte(Node* r) // iteration scheme ref： Data Structure P129
    {
        Stack S(_size);
        GoAlongLeftBranch(r, S);
        while(!S.empty())
        {
            Node* c=S.pop();
            Visit(c);
            GoAlongLeftBranch(c->right,S);
        }
        
    }
    
};

int SearchInterval(int*V, int a, int b, int e);
void ProperRebuild(int*A, int*B, int al, int ar, int bl, int br, int n, Node*& r);


int main(int argc, const char * argv[]) {
    // insert code here...
    int n;
    cin>>n;
    int* A=new int[n];
    int* B=new int[n];
    for(int i=0;i<n;i++)
    {
        cin>>A[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>B[i];
    }
    Node *r = new Node(A[0]);
    m++;
    ProperRebuild(A, B, 0, n, 0, n, n, r);
    Tree* T = new Tree(r,n);
    T->InorderIte(r);
    
    //T->InorderRec(r);
    cout<<endl;
    return 0;
}

void ProperRebuild(int* A, int* B, int al, int ar, int bl, int  br, int n, Node*& r){
    // the proporty of proper tree
    if(n<2)
    {
        return;
    }
    int i=al;
    int j=br-1;
    int a,b;
    int el=A[++i];
    Node* le=new Node(el);
    r->left = le;
    m++;
    a = bl;
    b = br-1;
    int locB = SearchInterval(B, a, b, el);
    int er = B[--j];
    Node* re=new Node(er);
    r->right = re;
    m++;
    a = al+2;
    b = ar;
    int locA = SearchInterval(A, a, b, er);
    ProperRebuild(A, B, i, locA, bl, locB+1, locA-i,r->left);
    ProperRebuild(A, B, locA, ar, locB+1, br-1, ar-locA,r->right);
}

int SearchInterval(int*V, int a, int b, int e){
    for(int i=a; i<b; i++)
    {
        if(V[i]==e){
            return i;
        }
    }
    return b;
}
