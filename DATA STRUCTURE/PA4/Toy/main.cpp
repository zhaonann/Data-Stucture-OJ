#include <cstdio>
#include <string.h>

#define L 40320
#define MaxBoard 8

//design ref https://www.cnblogs.com/Inkblots/p/5093255.html
struct Board{
    int hval;
    int level;
    Board(int h=0, int l=0){
        hval = h;
        level = l;
    }
    Board& operator=(Board& mb){
        hval = mb.hval;
        level = mb.level;
        return *this;
    }
};

class Queue{
public:
    int len;
    int header;
    int tailer;
    Board data[L];
    Queue(){
        len=0;
        header=-1;
        tailer=-1;
    }
    bool Empty(){
        return len==0?true:false;
    }
    void FisrtEnQueue(Board mb){
        header = tailer = 0;
        data[header] = mb;
        ++len;
    }
    void EnQueue(Board mb){
        tailer = (tailer+1)%L;
        data[tailer] = mb;
        ++len;
    }
    Board DeQueue(){
        Board tmp = data[header];
        header = (header+1)%L;
        --len;
        return tmp;
    }
};

int Ans[L];
static const int Factorial[MaxBoard] = {1,1,2,6,24,120,720,5040};

void Erase(char p[], int len, int i);
void ReCantor(int hval, char (&m)[8]);
int HashValue(int Ele[]);
int HashValue(char Ele[]);
Board Tranfer1(Board mb, int index);
Board InvTranfer(Board mb, int index);
void Create(Board tmp);

int main(int argc, const char * argv[]) {

    int N=0;
    int loc = 0;
    scanf("%d", &N);
    Board Tree(0,0);
    memset(Ans,-1,sizeof(Ans));
    Create(Tree);
    int In[MaxBoard];
    for(int i=0; i<N; i++){
        for(int j=0; j<MaxBoard; j++){
            scanf("%d",&In[j]);
        }
        loc = HashValue(In);
        printf("%d\n",Ans[loc]);
    }
    return 0;
}

void Create(Board tmp){
    Ans[tmp.hval] = 0;
    Queue Q;
    Q.FisrtEnQueue(tmp);
    while(!Q.Empty()){
        Board tmp1 = Q.DeQueue();
        for(int i=0; i<3; i++){ // three transforms
            Board t1 = InvTranfer(tmp1, i);
            if(Ans[t1.hval]==-1 || (Ans[t1.hval]!=-1 && t1.level < Ans[t1.hval])){
                Ans[t1.hval] = t1.level;
                Q.EnQueue(t1);
            }
        }
    }
}

Board InvTranfer(Board mb, int index){
    Board t1;
    t1.level = mb.level + 1;
    char t[MaxBoard];
    char m[MaxBoard]={};
    ReCantor(mb.hval, m);
    int span = MaxBoard>>1;
    if(index==0){ // Exchange two lines
        for(int i=0; i < MaxBoard; i++){
            t[i] = m[MaxBoard-1-i];
        }
        t1.hval = HashValue(t);
    }else if(index==1){ // right shifting
        for(int i=0; i<span-1; i++){
            t[i] = m[i+1];
            t[i+span+1] = m[i+span];
        }
        t[3] = m[0];
        t[4] = m[7];
        t1.hval = HashValue(t);
    }else if(index==2){ // center rotation
        int span2 = span>>1;
        for(int j=0,i=0; j<span2; j++){
            t[i] = m[i];
            t[i+3] = m[i+3];
            i+=span;
        }
        t[1] = m[2];
        t[2] = m[5];
        t[5] = m[6];
        t[6] = m[1];
        t1.hval = HashValue(t);
    }
    return t1;
}

int HashValue(char Ele[]){
    int code=0;
    int tmp=0;
    for(int i=0; i<MaxBoard-1; i++){
        tmp=0;
        for(int j=i+1; j<MaxBoard; j++){
            if(Ele[j]<Ele[i]){
                ++tmp;
            }
        }
        code += tmp * Factorial[MaxBoard-1-i];
    }
    return code;
}

int HashValue(int Ele[]){
    int code=0;
    int tmp=0;
    for(int i=0; i<MaxBoard-1; i++){
        tmp=0;
        for(int j=i+1; j<MaxBoard; j++){
            if(Ele[j]<Ele[i]){
                ++tmp;
            }
        }
        code += tmp * Factorial[MaxBoard-1-i];
    }
    return code;
}

void ReCantor(int hval, char(&tmp)[8]){
    char pattern[MaxBoard];
    for(int i=1; i<=MaxBoard; i++){
        pattern[i-1] = i+'0';
    }
    int quot = 0; //quotient
    int rem = 0; //remainder
    for(int i=MaxBoard-1; i>=0; i--){
        quot = hval/Factorial[i];
        rem = hval%Factorial[i];
        tmp[MaxBoard-1-i]=pattern[quot];
        Erase(pattern, i+1, quot);
        hval = rem;
    }
}

void Erase(char p[], int len, int i){
    for(int j=i; j<len-1; j++){
        p[j] = p[j+1];
    }
}
