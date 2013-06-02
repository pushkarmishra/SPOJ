/*
Algo: Segment tree with Lazy Propagation and Binary Search
Complexity: N*LogN
*/

#include <cstdio>
#define gc getchar_unlocked
static int N, M, L, qs, qe, chk, ANS=0;
struct node{int c0, c1, f;} ST[5000000];
 
void scan(int &x){
    register int c = gc(); x = 0; for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
inline void build(int x, int y, int n){
    if(x==y){
        ST[n].c0=0; ST[n].c1=1; return;
    }
    int m=(x+y)>>1;
    build(x, m, 2*n+1); build(m+1, y, 2*n+2);
    ST[n].c0=ST[2*n+1].c0+ST[2*n+2].c0;
    ST[n].c1=ST[2*n+1].c1+ST[2*n+2].c1;
}
inline void update(int x, int y, int n){
    if(y<qs || qe<x) return;
    if(qs<=x && y<=qe){
        int tmp=ST[n].c0; ST[n].c0=ST[n].c1; ST[n].c1=tmp;
        ST[n].f+=1; return;
    }
    int m=(x+y)>>1;
    update(x, m, 2*n+1); update(m+1, y, 2*n+2);
    ST[n].c0=ST[2*n+1].c0+ST[2*n+2].c0;
    ST[n].c1=ST[2*n+1].c1+ST[2*n+2].c1;
    if(ST[n].f%2){int tmp=ST[n].c0; ST[n].c0=ST[n].c1; ST[n].c1=tmp;}
}
inline void bsearch(int x, int y, int cf, int ct, int n){
    if(ST[n].c0+ct<L && cf%2) return;
    else if(ST[n].c1+ct<L && !(cf%2)) return;
    if(x==y){
        if(cf%2 && ST[n].c0+ct==L) ANS=x;
        else if(ST[n].c1+ct==L && !(cf%2)) ANS=x;
        return;
    }
    int q=ST[n].f+cf, m=(x+y)>>1; chk=1;
    int tmp=(q%2)? ST[2*n+1].c0+ct: ST[2*n+1].c1+ct;
    int tmp1=(q%2)? ST[2*n+2].c0+tmp: ST[2*n+2].c1+tmp;
    if(tmp>=L) {bsearch(x, m, q, ct, 2*n+1); return;}
    if(tmp1>=L){bsearch(m+1, y, q, tmp, 2*n+2); return;}
}
 
int main(){
    scan(N); scan(M); scan(L);
    build(1, N, 1);
    while(M--){
        scan(qs); scan(qe); chk=0; ANS=0;
        update(1, N, 1); bsearch(1, N, 0, 0, 1);
        (!chk)? printf("AC?\n"): printf("%d\n", ANS);
    }
    return 0;
}
