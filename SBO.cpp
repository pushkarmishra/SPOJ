/*
Algo: Segment Tree with Lazy Propagation
Complexity: N*LogN
*/

#include <cstdio>
#include <vector>
using namespace std;

vector< vector<int> >v(100001);
struct node{int maxc, f;} ST[2500050];
static int qs, qe, val, chk=0, N, ANS, S[500010];

inline void update(int x, int y, int n){
    if(y<qs || qe<x || qs>qe) return;
    if(qs<=x && y<=qe){
        if(chk==0){ST[n].maxc=val+ST[n].f;}
        else if(chk==1){ST[n].f+=1; ST[n].maxc+=1;}
        else if(chk==-1){ST[n].f-=1; ST[n].maxc-=1;}
        return;
    }
    int m=(x+y)>>1;
    update(x, m, 2*n); update(m+1, y, 2*n+1);
    ST[n].maxc=(ST[2*n].maxc>ST[2*n+1].maxc)? ST[2*n].maxc: ST[2*n+1].maxc;
    ST[n].maxc+=ST[n].f;
}

int main(){
    scanf("%d", &N); int c=0;
    for(int i=0; i<N; ++i)scanf("%d", &S[i]);
    for(int i=0; i<v.size(); ++i)v[i].push_back(1);
    for(int i=0; i<N; ++i)v[S[i]].push_back(i);
    for(int i=0; i<v.size(); ++i){v[i].push_back(0);v[i].push_back(0);}
    for(int i=0; i<N; ++i){
        if(v[S[i]][1]==i){val=++c; qs=qe=i; update(0, N-1, 1);}
        else if(v[S[i]][2]==i){val=--c; qs=qe=i; update(0, N-1, 1);}
        else if(v[S[i]][2]<i){val=c; qs=qe=i; update(0, N-1, 1);}
    }
    ANS=ST[1].maxc;
    for(int i=0; i<N; ++i){
        int t=v[S[i]][0]++;
        chk=0; qs=qe=i; val=-1000000; update(0, N-1, 1);
        chk=-1; qs=v[S[i]][t]+1; qe=(v[S[i]][t+1]==0)?N-1:v[S[i]][t+1]-1; update(0, N-1, 1);
        if (v[S[i]][t+1]!=0)
            {chk=1; qs=v[S[i]][t+1]; qe=(v[S[i]][t+2]==0)?N-1:v[S[i]][t+2]-1; update(0, N-1, 1);}
        if(ST[1].maxc>ANS) ANS=ST[1].maxc;
    }
    printf("%d\n", ANS);
    return 0;
}
