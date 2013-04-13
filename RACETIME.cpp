/*
Algo: Segment Tree
Complexity: (N+Q)*Log(N+Q)
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define gc getchar_unlocked

void scan(long &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc()){
        if (c>=65 && c<=92) {x=c; return;}
    }
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

struct s{long minn, maxn;} st[500001];
struct a{long val; int n;}A[100500];
struct t{int s, e, n;} temp[500001];
static long N, Q, qs, qe, updidx, K, updval, in;

inline void build(int x, int y, int node){
    if (x==y){
        st[node].minn=st[node].maxn=A[x].val;
        A[x].n=node;
        return;
    }
    int mid=(x+y)/2;
    build(x, mid, 2*node+1); build(mid+1, y, 2*node+2);
    st[node].minn= min(st[2*node+1].minn, st[2*node+2].minn);
    st[node].maxn= max(st[2*node+1].maxn, st[2*node+2].maxn);
}

void update(){
    int idx=A[updidx].n;
    st[idx].maxn=st[idx].minn=updval; idx=(idx-1)/2;
    while(idx>0){
        st[idx].minn= min(st[2*idx+1].minn, st[2*idx+2].minn);
        st[idx].maxn= max(st[2*idx+1].maxn, st[2*idx+2].maxn);
        idx=(idx-1)/2;
    }
}

int query(){
    int i=1, j=1, ans=0, chk=1;
    temp[i].s=1; temp[i].e=N; temp[i].n=1;

    while(j<=i){
        int ss=temp[j].s, se=temp[j].e, node=temp[j++].n;
        if (ss>qe || se<qs) ans=ans;
        else{
            chk=1;
            if (qs<=ss && se<=qe){
                if (st[node].maxn<=K) {ans+=se-ss+1; chk=0;}
            }
            if (ss<se && chk){
                int mid=(ss+se)/2;
                temp[++i].s=ss; temp[i].e=mid; temp[i].n=2*node+1;
                temp[++i].s=mid+1; temp[i].e=se; temp[i].n=2*node+2;
            }
        }
    }
    return ans;
}

int main()
{
    scan(N); scan(Q);
    for (int i=1; i<=N; ++i) scan(A[i].val);
    build(1, N, 1);

    while(Q--){
        scan(in);
        if (in==67){
            scan(qs); scan(qe); scan(K);
            printf("%d\n", query());
        }

        else{
            scan(updidx); scan(updval);
            A[updidx].val=updval;
            update();
        }
    }
    return 0;
}
