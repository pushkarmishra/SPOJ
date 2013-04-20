/*
Algo: Segment Tree
Complexity: N*LogN
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
 
struct segtree{int l, r, b;} st[500004], ans;
static int A[100010], qs, qe, N, Q;
 
inline void build(int x, int y, int n){
    if (x==y){
        st[n].b=1; st[n].l=st[n].r=x;
        return;
    }
    int mid=(x+y)>>1;
    build(x, mid, 2*n+1); build(mid+1, y, 2*n+2);
    
    st[n].l=(A[mid+1]==A[x])?st[2*n+2].l: st[2*n+1].l;
    st[n].r=(A[mid]==A[y])?st[2*n+1].r: st[2*n+2].r;
    
    if (A[mid]==A[mid+1])
        st[n].b=max(max(st[2*n+1].b, st[2*n+2].b), st[2*n+2].l-st[2*n+1].r+1);
    else
        st[n].b=max(st[2*n+1].b, st[2*n+2].b);
}
 
inline void query(segtree &ans, int x, int y, int n){
    if (qs<=x && y<=qe) {ans=st[n]; return;}
    
    int mid=(x+y)>>1;
    if(qe<=mid) {query(ans, x, mid, 2*n+1); return;}
    if (qs>mid) {query(ans, mid+1, y, 2*n+2); return;}
    
    segtree left, right;
    query(left, x, mid, 2*n+1); query(right, mid+1, y, 2*n+2);
    
    ans.l=(A[mid+1]==A[x])?right.l: left.l;
    ans.r=(A[mid]==A[y])?left.r: right.r;
    
    if (A[mid]==A[mid+1])
        ans.b=max(max(left.b, right.b), right.l-left.r+1);
    else
        ans.b=max(left.b, right.b);
}
 
int main()
{
    while(1){
        scanf("%d", &N); if (!N) return 0;
        scanf("%d", &Q);
        for(int i=1; i<=N; ++i) scanf("%d", &A[i]);
        build(1, N, 1);
    
        while(Q--){
            scanf("%d %d", &qs, &qe);
            query(ans, 1, N, 1);
            printf("%d\n", ans.b);
        }
    }
    return 0;
}
