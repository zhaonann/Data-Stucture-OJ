//
//  main.cpp
//  PArange
//
//  Created by nan zhao on 2021/2/4.
//  Copyright © 2021 nan zhao. All rights reserved.
//
#include <cstdio>

const int SZ = 1<<20;
struct fastio{   //fast io
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

int BinarySearch(int* vec, int n, int e);
int RangeSearch(int* vec, int n, int a, int b);
void Merge(int*vec, int low, int high);
void MergeSort(int* vec, int low, int high);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int n=0; // the size of S
    int m=0; // the number of queries
    scanf("%d%d",&n,&m);
    int* vec = new int[n]; // store the integral points
    for(int i=0; i<n; i++)
    {
        scanf("%d",&vec[i]);
    }
    MergeSort(vec, 0, n);
    int a,b;
    int result=0;
    while(m--)
    {
        scanf("%d%d",&a,&b);
        result = RangeSearch(vec, n, a, b);
        printf("%d\n",result);
    }
    return 0;
}

int BinarySearch(int* vec, int n, int e)
{
    int low=0;
    int high =n;
    int middle = 0;
    while(low<high)
    {
        middle = (low + high) >> 1;
        (e < vec[middle]) ? high = middle : low = middle+1;
        
    }
    // failure location
    return --low;
}

int RangeSearch(int* vec, int n,  int a, int b){
    // binary searching
    
    int loc1 = BinarySearch(vec, n, a);
    int loc2 = BinarySearch(vec, n, b);
    int sum=0;

    if(loc1 == loc2)
    {
        sum = 0;
    }
    else
    {
        sum = loc2-loc1;
    }
    if(loc1!=-1 && vec[loc1]==a)
    {
        sum++;
    }
    return sum;
}


void Merge(int* vec, int low, int middle, int high)
{
    // copying the first part to vec
    int la = middle - low; // length of left part
    int* aVec = new int[la];
    int aPosi = low;
    for(int i=0; i<la; i++)
    {
        aVec[i] = vec[aPosi++];
    }
    int lb = high-middle; // length of right part
    int i=low;
    int k=middle;
    int j=0;
    for(; j<la;)
    {
        if((k>=high) || (aVec[j]<=vec[k]))
        {
            vec[i++] = aVec[j++];
        }
        else if((k<high)&&(aVec[j]>vec[k]))
        {
            vec[i++] = vec[k++];
        }
    }
}




void MergeSort(int* vec, int low, int high)
{
    if (high-low==1)
    {
        return;
    }
    int middle = (low+high) >> 1;
    MergeSort(vec, low, middle);
    MergeSort(vec, middle, high);
    Merge(vec, low, middle, high);
}
