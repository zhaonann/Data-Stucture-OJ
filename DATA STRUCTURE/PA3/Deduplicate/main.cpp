//
//  main.cpp
//  Deduplicate
//
//  Created by nan zhao on 2021/2/14.
//  Copyright © 2021 nan zhao. All rights reserved.
//

#include <iostream>
#include <string.h>
#define L 600001 // ref https://blog.csdn.net/qq_37729102/article/details/84109062
//separate chaining

using namespace std;

struct Candidates{
    char name[41];
    int bitcode; // 0 no duplicate 1 repeat
    Candidates* next;
    Candidates(){
        bitcode = 0;
        next = NULL;
    }
}htable[L];

class Hash{
public:
    Hash(){
    }
    bool Insert(Candidates* can){
        size_t n=strlen(can->name);
        unsigned int h=0;
        for(size_t i=0; i<n; i++){
            h = (h<<5) | (h >> 27);
            h+=(unsigned int)can->name[i];
        }
        unsigned int loc = h % L; // ref https://blog.csdn.net/Seasoon_/article/details/84039377
        Candidates* tmp = htable[loc].next;
        while(tmp){
            if(0==strcmp(tmp->name, can->name)){
                if(tmp->bitcode==0){
                    tmp->bitcode=1;
                    return false;
                }else{
                    return true;
                }
            }
            tmp = tmp->next;
        }
        can->next = htable[loc].next;
        htable[loc].next = can;
        return true;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    int n=0;
    cin>>n;
    Hash In;
    for(int i=0; i<n; i++){
        Candidates* can = new Candidates;
        cin>>can->name;
        if(!In.Insert(can)){
            cout<<can->name<<endl;
        }
    }
    return 0;
}

