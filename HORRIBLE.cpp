/*
Algo: Segment Tree
Complexity: N*LogN
*/

#include <cstdio>
#include <cstring>
using namespace std;

struct segtree{long long sum, v;} st[500004];
static long long A[100010], ANS, V;
int qs, qe, N, Q, T, in;

inline void update(int x, int y, int n){
    if (y<qs || qe<x) return;
    if (qs<=x && y<=qe){
        st[n].sum+=(V*(y-x+1));
        st[n].v+=V; return;
    }
    int mid=(x+y)>>1;
    update(x, mid, 2*n+1); update(mid+1, y, 2*n+2);
    st[n].sum=st[2*n+1].sum+st[2*n+2].sum + st[n].v*(y-x+1);
}

void query(int x, int y, int n, long long v){
    if (y<qs || qe<x) return;
    if (qs<=x && y<=qe){
        ANS+= ((v)*(y-x+1) + st[n].sum); return;
    }
    int mid=(x+y)>>1;
    query(x, mid, 2*n+1, v+st[n].v);
    query(mid+1, y, 2*n+2, v+st[n].v);
}

int main()
{
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &N, &Q);
        memset(st, 0, sizeof st);
        
        while(Q--){
            scanf("%d %d %d", &in, &qs, &qe);
            if(in){
                ANS=0; query(1, N, 1, 0);
                printf("%lld\n", ANS);
            }
            else{
                scanf("%lld", &V);
                update(1, N, 1);
            }
        }
    }
    return 0;
}
