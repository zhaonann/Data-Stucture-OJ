//
//  main.cpp
//  Temperature
//
//  Created by nan zhao on 2021/2/25.
//  Copyright © 2021 nan zhao. All rights reserved.
//
#include <stdio.h>
#include "temperature.h"
//#include "temperature_lib.c"

typedef struct _station_type
{
    int x, y;
    int temp;
} station_type;

typedef struct _y_axis{
    station_type * station;
    int lc;
    int rc;
}y_axis;

struct node{
    station_type * station;
    node * lc;
    node * rc;
    y_axis * y_addr;
    int numOfY;
};

static int n, m;
static int last_response, query_index;
static station_type stations[50000];

void MergeSort(station_type sta[], int low, int high);
void Merge(station_type sta[], int low, int mi, int high);

void BuildRangeTree(station_type sta[], int low, int high, node *&root);

node* FindSplitNode(int x1, int x2, int y1, int y2, node* root);
void OneDimRangeQuery(node* subtree, int start, int y1, int y2, long long int &avg_temp, long long int &total_num);
int BinSearch(int y1, y_axis sta_y[], int low, int high);
int TwoDimRangeQuery(int x1, int y1, int x2, int y2, node* root);


int main(int argc, const char * argv[]) {
    // insert code here...
    n = GetNumOfStation();
    for(int i = 0; i < n; i++){
        int x, y, temp;
        GetStationInfo(i, &x, &y, &temp);
        stations[i].x = x;
        stations[i].y = y;
        stations[i].temp = temp;
    }
    MergeSort(stations, 0, n);
    node *root = NULL;
    BuildRangeTree(stations, 0, n, root);
    int x1, y1, x2, y2;
    while(GetQuery(&x1, &y1, &x2, &y2)){
        int temp = TwoDimRangeQuery(x1, y1, x2, y2, root);
        Response(temp);
    }
    return 0;
}

void Merge(station_type sta[], int low, int mi, int high){
    int leftlength = mi - low;
//    int rightlength = high - mi;
    station_type tmp[leftlength];
    for(int i = 0; i < leftlength; i++){
        tmp[i].x = sta[low+i].x;
        tmp[i].y = sta[low+i].y;
        tmp[i].temp = sta[low+i].temp;
    }
    int i = low;
    int j = mi;
    int k = 0; //index for tmp
    // merge according to x axis
    for(; k < leftlength; i++){
        if(j >= high || tmp[k].x < sta[j].x || (tmp[k].x == sta[j].x && tmp[k].y < sta[j].y)){

            sta[i].x = tmp[k].x;
            sta[i].y = tmp[k].y;
            sta[i].temp = tmp[k].temp;
            k++;
        }
        else if(j < high && (tmp[k].x > sta[j].x || (tmp[k].x == sta[j].x && tmp[k].y > sta[j].y))){
            sta[i].x = sta[j].x;
            sta[i].y = sta[j].y;
            sta[i].temp = sta[j].temp;
            j++;
        }
    }
}

void MergeSort(station_type sta[], int low, int high){
    // sorting according to axis, 0->x;1->y
    if(high - low <= 1){
        return;
    }
    int mi = (low + high) >> 1;
    MergeSort(sta, low, mi);
    MergeSort(sta, mi, high);
    Merge(sta, low, mi, high);
}

void BuildRangeTree(station_type sta[], int low, int high, node *&root){
    if(high - low == 0){
        root = NULL;
        return;
    }
    y_axis *sta_y = new y_axis[high - low];
    root = new node;
    
    if(high - low == 1){
        root->station = &sta[low];
        root->lc = NULL;
        root->rc = NULL;
        
        sta_y[0].station = &sta[low];
        sta_y[0].lc = -1;
        sta_y[0].rc = -1;
        root->y_addr = sta_y;
        root->numOfY = 1;
        return;
    }
    
    int mi = (low + high - 1) >> 1;
    root->station = &sta[mi];
    
    BuildRangeTree(sta, low, mi + 1, root->lc);
    BuildRangeTree(sta, mi + 1, high, root->rc);
    
    int leftlength = mi + 1 - low;
    int rightlength = high - mi - 1;
    int i = 0;
    int j = 0; //index for rc
    int k = 0; //index for lc
    // merge according to y axis
    for(; k < leftlength; ){
        if(j >= rightlength || root->lc->y_addr[k].station->y <= root->rc->y_addr[j].station->y){
            sta_y[i].station = root->lc->y_addr[k].station;
            sta_y[i].lc = k;
            if(j >= rightlength){
                sta_y[i].rc = -1;
            }else{
                sta_y[i].rc = j;
            }
            k++;
        }else if(j < rightlength && root->lc->y_addr[k].station->y > root->rc->y_addr[j].station->y){
            sta_y[i].station = root->rc->y_addr[j].station;
            sta_y[i].rc = j;
            sta_y[i].lc = k;
            j++;
        }
        if(i - 1 >= 0 && sta_y[i].station->y == sta_y[i-1].station->y){
            sta_y[i].lc = sta_y[i-1].lc;
            sta_y[i].rc = sta_y[i-1].rc;
        }
        i++;
    }
    if(k >= leftlength && j < rightlength){
        for(; j < rightlength;){
            sta_y[i].station = root->rc->y_addr[j].station;
            if(i - 1 >= 0 && sta_y[i].station->y == sta_y[i-1].station->y){
                sta_y[i].lc = sta_y[i-1].lc;
                sta_y[i].rc = sta_y[i-1].rc;
            }else{
                sta_y[i].rc = j;
                sta_y[i].lc = -1;
            }
            j++;
            i++;
        }
    }
    root->y_addr = sta_y;
    root->numOfY = high - low;
}

node* FindSplitNode(int x1, int x2, int y1, int y2, node *root){
    node *v = root;
    while(!(v->lc == NULL && v->rc == NULL) && (x2 < v->station->x or x1 > v->station->x or (x2 == v->station->x && y2 <= v->station->y) or (x1 == v->station->x && y1 > v->station->y))){
        if(x2 < v->station->x or (x2 == v->station->x && y2 <= v->station->y)){
            v = v->lc;
        }else{
            v = v->rc;
        }
    }
    return v;
}
int BinSearch(int y1, y_axis sta_y[], int low, int high){
    while(high > low){
        int mi = (low + high - 1) >> 1;
        if(sta_y[mi].station->y < y1){
            low = mi + 1;
        }else if(sta_y[mi].station->y > y1){
            high = mi;
        }else{
            return mi;
        }
    }
    return low;
}

void OneDimRangeQuery(node* subtree, int start, int y1, int y2, long long int &avg_temp, int &total_num){
    if(-1 == start){
        return;
    }
    for(int i = start; i < subtree->numOfY; i++){
        if(subtree->y_addr[i].station->y <= y2){
            avg_temp += subtree->y_addr[i].station->temp;
            total_num ++;
        }else if(subtree->y_addr[i].station->y > y2){
            break;
        }
    }
}

int TwoDimRangeQuery(int x1, int y1, int x2, int y2, node* root){
    if(root == NULL){
        return 0;
    }
    long long int avg_temp = 0;
    int total_num = 0;
    int result = 0;
    node *v = FindSplitNode(x1, x2, y1, y2, root);
    if(v->rc == NULL && v->lc == NULL){ // v is a leaf, only one element
        if(v->station->x >= x1 && v->station->x <= x2 && v->station->y >= y1 && v->station->y <= y2){
            result = v->station->temp;
        }else{
            result = 0;
        }
    }else{ // v is not a leaf
        int loc = BinSearch(y1, v->y_addr, 0, v->numOfY);
        if(loc == v->numOfY){ // empty set
            avg_temp = 0;
        }else{ // follow the path to left
            int lc = v->y_addr[loc].lc;
            node *v_lc = v->lc;
            while(!(v_lc->rc == NULL && v_lc->lc == NULL)){ // left branch is not a leaf
                if(lc == -1){
                    break;
                }
                if(x1 < v_lc->station->x || (x1 == v_lc->station->x && y1 <= v_lc->station->y)){
                    // searching for y , y1, y2
                    OneDimRangeQuery(v_lc->rc, v_lc->y_addr[lc].rc, y1, y2, avg_temp, total_num);
                    lc = v_lc->y_addr[lc].lc;
                    v_lc = v_lc->lc;
                }else{
                    lc = v_lc->y_addr[lc].rc;
                    v_lc = v_lc->rc;
                }
            }
            // v_lc is a leaf
            if(v_lc->station->x >= x1 && v_lc->station->x <= x2 && v_lc->station->y >= y1 && v_lc->station->y <= y2){
                avg_temp += v_lc->station->temp;
                total_num++;
            }
            // following the path to right
            int rc = v->y_addr[loc].rc;
            node *v_rc = v->rc;
            while(!(v_rc->rc == NULL && v_rc->lc == NULL)){ // left branch is not a leaf
                if(rc == -1){
                    break;
                }
                if(x2 > v_rc->station->x || (x2 == v_rc->station->x && y2 > v_rc->station->y)){
                    // searching for y , y1, y2
                    OneDimRangeQuery(v_rc->lc, v_rc->y_addr[rc].lc, y1, y2, avg_temp, total_num);
                    rc = v_rc->y_addr[rc].rc;
                    v_rc = v_rc->rc;
                }else{ // x2 < v_rc->station->x || (x2 == v_rc->station->x && y1 < v_rc->station->y)
                    rc = v_rc->y_addr[rc].lc;
                    v_rc = v_rc->lc;
                }
            }
            // v_rc is a leaf
            if(v_rc->station->x >= x1 && v_rc->station->x <= x2 && v_rc->station->y >= y1 && v_rc->station->y <= y2){
                avg_temp += v_rc->station->temp;
                total_num++;
            }
            if(total_num == 0){
                result = 0; // avoid division 0
            }else{
                result = avg_temp/total_num;
            }
        }
    }
    return result;
}
