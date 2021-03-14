//
//  main.cpp
//  PA2ZUMA
//
//  Created by nan zhao on 2021/2/3.
//  Copyright © 2021 nan zhao. All rights reserved.
//

#include <cstdio>
#include <stdio.h>
#include <string.h>

//TLE https://www.cnblogs.com/Inkblots/p/4893404.html

#define Max 150001000

static char Out[Max];
static unsigned int Loc=0;

struct ListNode{
    char data; // data field
    ListNode* pred;
    ListNode* succ; // point field
    ListNode(){}
    ListNode(char e, ListNode* p = NULL, ListNode* s = NULL):data(e),pred(p),succ(s){}

};

class List{
private:
    int _size;
    ListNode* header;
    ListNode* tailer;
protected:
    void init(){
        header = new ListNode;
        tailer = new ListNode;
        
        header->data = '-';
        header->succ = tailer;
        header->pred = NULL;
        
        tailer->data = '-';
        tailer->pred = header;
        tailer->succ = NULL;
        
        _size = 0;
    
    }
public:
    List() {init();}
    
    void insertAsLast(char e)
    {
        ListNode* newNode = new ListNode(e);
        newNode->succ = tailer;
        newNode->pred = tailer->pred;
        tailer->pred->succ = newNode;
        tailer->pred = newNode;
        _size ++;
    }
    
    void insertA(ListNode* p, char e)
    {// insert e as the successor of p
        ListNode* newNode = new ListNode(e);
        newNode->pred = p;
        newNode->succ = p->succ;
        p->succ->pred = newNode;
        p->succ = newNode;
        _size++;
    }
    
    void removeByInterval(ListNode* &pf, ListNode* &pb, int& n)
    {// remove n elements after p
        _size = _size - n;
        ListNode* tmp1 = pf->succ;
        ListNode* tmp2 = tmp1->succ;
        while(n--)
        {
            tmp1->succ = NULL;
            tmp1->pred = NULL;
            tmp1 = tmp2;
            tmp2 = tmp1->succ;
        }
        
        pf->succ = pb;
        pb->pred = pf;
    }
    
    void countSameElements(ListNode* p, char e, int& totalNumber, ListNode* & PosiFront, ListNode* & PosiBack)
    {// calculating the number of same elements
     // return the initial location
       
        int pCount = 0, sCount = 0; // the number of the same elements before and after
     
        // calculating the number of the same elements before
        ListNode* pNode = p;
        while(pNode!= header && pNode->data==e)
        {
            pCount++;
            pNode = pNode->pred;
        }
   
        // calculating the number of the same elements after
        ListNode* sNode = p->succ;
        while(sNode!=tailer && sNode->data==e)
        {
            sCount++;
            sNode = sNode->succ;
        }
        totalNumber = pCount + sCount;
        PosiBack = sNode;
        PosiFront = pNode;
    }
    
    void insertByPosi(int i, const char e)
    {
        if(i<0 || i>_size)
        {
            return;
        }
       
        ListNode* c = header;
        while(i--)
        {
            c = c->succ;
        }
        // first check
        int totalNumber = 0;
        ListNode* newLocBack = NULL;
        ListNode* newLocFront = NULL;
        countSameElements(c, e, totalNumber, newLocFront, newLocBack);
        
        if(totalNumber < 2)
        {
            insertA(c, e); // insert safely
            return;
        }else{
            removeByInterval(newLocFront, newLocBack, totalNumber);
            if(newLocFront == header||newLocBack == tailer)
            {
                return;
            }else{
                countSameElements(newLocFront, newLocFront->data, totalNumber, newLocFront, newLocBack);}
        }
        
        while(totalNumber >= 3)
        {// need to eliminate and further check
            
            removeByInterval(newLocFront, newLocBack, totalNumber);
            // totalNumber = 0;
            if(newLocFront == header||newLocBack == tailer)
            {
                break;
            }
            countSameElements(newLocFront, newLocFront->data, totalNumber, newLocFront, newLocBack);
        }
  
    }
    
    void output()
    {
        if(_size==0)
        {
            Out[Loc++] = '-';// '-' stands for an empty sequence
        }else{
            ListNode* c = header->succ;
            while(c->succ!=NULL)
            {
                Out[Loc++]=c->data;
                c = c->succ;
            }
        }
        Out[Loc++]='\n';
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    List ZumaList;
    char c1;
    scanf("%c",&c1);
    while(c1 != '\n')
    {
        ZumaList.insertAsLast(c1);
        scanf("%c",&c1);
    }
    int n=0;
    int posi=0;
    char data;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %c",&posi, &data);
        ZumaList.insertByPosi(posi, data);
        ZumaList.output();
    }
    printf("%s",Out);
    return 0;
}
