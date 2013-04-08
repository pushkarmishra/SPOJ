/*
Algo: Binary Search Tree
Complexity: N*LogN
*/

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define gc getchar_unlocked
 
void scan(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
 
struct s{int sol, lsize, rsize, p, r, l;} m[200001];
static int ranks, A[200001], ANS[200001], N, node, val;
 
inline int minimum(int idx){
    while(m[m[idx].l].sol!=0) idx=m[idx].l;
    return idx;
}
inline int successor(int idx){
    int idx1=m[idx].r;
    if (m[idx1].sol!=0) return minimum(idx1);
    int y=m[idx].p;
    while(m[y].sol!=0 && m[idx].sol==m[m[y].r].sol){
        idx=y;
        y=m[idx].p;
    }
    return y;
}
inline void insertion(s const& temp, int place, int idx){
    if (ranks>=place){
        m[idx].lsize+=1; int idx1=m[idx].l;
        ranks=ranks-m[idx].lsize+m[idx1].lsize+1;
        if (m[idx1].sol==0){
            m[node].sol=val; m[idx].l=node; m[node].l=0; m[node].r=0; m[node++].p=idx;
            return;
        }
        else insertion(temp, place, idx1);
    }
    else{
        m[idx].rsize+=1; int idx1=m[idx].r;
        ranks+=m[idx1].lsize+1;
        if (m[idx1].sol==0){
            m[node].sol=val; m[idx].r=node; m[node].l=0; m[node].r=0; m[node++].p=idx;
            return;
        }
        else insertion(temp, place, idx1);
    }
}
 
int main()
{
    int T; scan(T);
    while(T--){
        memset(m, 0, sizeof m);
        node=2; scan(N);
        for (int i=1; i<=N; ++i) scan(A[i]);
        m[1].sol=1;
 
        for (int i=2; i<=N; ++i){
            ranks=m[1].lsize+1;
            s temp; val=i;
            insertion(temp, i-A[i], 1);
        }
 
        int t=minimum(1);
        ANS[m[t].sol]=1;
        for (int i=2; i<=N; ++i){
            t=successor(t);
            ANS[m[t].sol]=i;
        }
 
        for (int i=1; i<=N; ++i)cout << ANS[i] << ' ';
        cout << '\n';
 
    }
    return 0;
}
