//
//  main.cpp
//  CycleKMP
//
//  Created by nan zhao on 2021/2/19.
//  Copyright © 2021 nan zhao. All rights reserved.
//
//  ref: https://blog.csdn.net/qq_37729102/article/details/84312738

#include <cstdio>
#include <string.h>
#include <stdio.h>
#define L 100000

int* BuiltTable(char* P, int len);
int KMP(char* C, char* B, int len);

int main(int argc, const char * argv[]) {
    // insert code here...
    char A[L+1]="",B[L+1]="";
    while (scanf("%s%s", A, B)!=EOF) {
        size_t lenA = strlen(A);
        char C[(lenA<<1)+1];
        for(int i=0; i<strlen(A); i++){
            C[i] = A[i];
            C[i+lenA] = A[i];
        }
        if(lenA!=strlen(B)){
            printf("NO\n");
        }else{
            if(KMP(C,B,(int)strlen(A)) <= lenA){
                printf("YES\n");
                
            }else{
                printf("NO\n");
            }
        }
    }
    return 0;
}

int KMP(char* C, char* B, int len){
    int* N = BuiltTable(B, len);
    int j = 0; int t = 0;
    while( j < (len << 1) && t < len){
        if(0>t || C[j]==B[t]){
            j++; t++;
        }else{
            t = N[t];
        }
    }
    delete [] N;
    return j-t;
}

int* BuiltTable(char* P, int len){
    int *N = new int[L+1];
    int t = N[0] = -1;
    int j = 0;
    while( j < len-1){
        if( 0 > t || P[j] == P[t]){
            j++; t++;
            N[j] = ( P[j] == P[t] ? N[t] : t );
        }else{
            t = N[t];
        }
    }
    return N;
}
