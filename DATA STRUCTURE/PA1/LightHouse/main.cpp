//
//  main.cpp
//  PA
//
//  Created by nan zhao on 2020/12/30.
//  Copyright © 2020 nan zhao. All rights reserved.
//
//
#include <cstdio>
#include <stdio.h>

#define MaxLen 4000010

struct LightHouse{
    int x; // x coordinate
    int y; // y coordinate
};

void Mergesort(LightHouse LH[], int low, int high);
void Merge(LightHouse LH[], int low, int mi, int high);

long long InvInside(LightHouse LH[], int low, int high);
long long InvBetween(LightHouse LH[], int low, int mi, int high);

LightHouse* B = new LightHouse[MaxLen>>1]; // assitant array

int main(int argc, const char * argv[]) {
    // insert code here...
    // input
    int n;
    scanf("%d", &n);
    LightHouse* LH = new LightHouse[n]; // variable-sized
    for(int i=0; i<n; i++)
    {
        scanf("%d",&LH[i].x);
        scanf("%d",&LH[i].y);
    }
    
    // sorting by x coordinates
    Mergesort(LH, 0, n);
    
    // sorting by y coordinates and counting inversion W
    long long oppo_total_inv = InvInside(LH, 0, n);
    // (n,2) - total_inv
    //long long result = n*(n-1)/2 - total_inv;
    printf("%lld\n",oppo_total_inv);
    return 0;
}

void Merge(LightHouse LH[], int low, int mi, int high){
    
    int ll = mi-low; // the length of left part
    int rl = high-mi; // the length of right part
    // copy LH[low,mi] to B[] global variable
    for(int i=0; i<ll; i++)
    {
        B[i].x = LH[low+i].x;
        B[i].y = LH[low+i].y;
    }
    // locate the beginning of right part
    LightHouse* C = &LH[0+mi];
    // compare B and C, and tranfer to LH
    for(int i=low,j=0,k=0; j<ll; )
    {
        if((k<rl)&&(B[j].x > C[k].x))
        {
            LH[i].x=C[k].x; // C belongs to LH
            LH[i++].y=C[k++].y;
        }
        else if((k>=rl)||(B[j].x < C[k].x))
        {
            LH[i].x=B[j].x;
            LH[i++].y=B[j++].y;
        }
    }
}

void Mergesort(LightHouse LH[], int low, int high){
    // sortint by x coordinates
    if(high-low < 2)
    {
        return;
    }
    int mi = ( low + high ) >> 1;
    // Dividing
    Mergesort(LH, low, mi); // sorting left part
    Mergesort(LH, mi, high); // sorting right part
    // combining
    Merge(LH, low, mi, high); // merge two parts
}

long long InvBetween(LightHouse LH[], int low, int mi, int high){
    //sorting by y coordinates and counting inv
    
    int ll = mi-low; // the length of left part
    int rl = high-mi; // the length of right part
    long long ci = 0; // the number of invertion
    // copy LH[low,mi] to B[] global variable
    for(int i=0; i < ll; i++)
    {
         //B[i].x=LH[low+i].x;
         B[i].y=LH[low+i].y;
    }
    // locate the beginning of right part
    LightHouse* C = &LH[0+mi];
    // compare B and C, and tranfer to LH
//    //counting inv
//    for(int k=0; k<rl; k++){
//        int j=0;
//        for(; j<ll; j++)
//        {
//            if(LH[low+j].y>LH[mi+k].y)
//            {
//                break;
//            }
//        }
//        ci += ll-j; // accumulating the number of invertion
//    }
//
     for(int i=low,j=0,k=0; j<ll; )
     {
         if((k<rl)&&(B[j].y>C[k].y))
         {
             //ci += ll - j; //countint inv
             LH[i].x=C[k].x; // C belongs to LH
             LH[i++].y=C[k++].y;
         }
         if((k>=rl)||(B[j].y<C[k].y))
         {
             if(B[j].y<C[k].y){
                 ci += rl - k;
             }
             LH[i].x=B[j].x;
             LH[i++].y=B[j++].y;
         }
     }
     return ci;
}

long long InvInside(LightHouse LH[], int low, int high){
    
    if(high-low < 2)
    {
        return 0;
    }
    int mi = ( low + high ) >> 1;
    // Dividing
    long long li = InvInside(LH, low, mi); // counting inv in left part
    long long ri = InvInside(LH, mi, high); // counting inv in right part
    // Combining
    long long ti = InvBetween(LH, low, mi, high); // counting inv in two parts
    return li+ri+ti;
    
}
