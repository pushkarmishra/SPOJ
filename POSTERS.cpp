/*
Algo: Segment Tree
Complexity: N*LogN
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

struct segtree{int l, r, v;} st[300000], Q[50000];
static int N, qs, qe, A[250000], T, K, idx;
vector<int> vec; map <long, int> chk;

inline void build(int x, int y, int n){
    if(x==y){
        st[n].l=st[n].r=A[x]; return;
    }
    int mid=(x+y)>>1;
    build(x, mid, 2*n+1); build(mid+1, y, 2*n+2);
    st[n].l=st[2*n+1].l; st[n].r=st[2*n+2].r;
}

inline void update(int x, int y, int n){
    if (A[x]>qe || A[y]<qs) return;

    if (qs<=A[x] && A[y]<=qe){
        st[n].v= K; return;
    }
    int mid=(x+y)>>1;
    update(x, mid, 2*n+1); update(mid+1, y, 2*n+2);
}

inline void query(int x, int y, int n, int v){
    if (x==y){
        v=(st[n].v==0 || st[n].v<v)? v: st[n].v;
        if(!chk[v]) {vec.push_back(v); chk[v]=1;}
        return;
    }
    int mid=(x+y)>>1, v1, v2;
    v1=(st[2*n+1].v==0 || st[2*n+1].v<v)? v: st[2*n+1].v;
    v2=(st[2*n+2].v==0 || st[2*n+2].v<v)? v: st[2*n+2].v;
    query(x, mid, 2*n+1, v1); query(mid+1, y, 2*n+2, v2);
}

int main()
{
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N); K=idx=0;
        chk.clear(); chk[0]=1; memset(st, 0, sizeof st);
        for (int i=1; i<=N; ++i){
            scanf("%d %d", &Q[i].l, &Q[i].r);
            if(!chk[Q[i].l]){A[++idx]=Q[i].l; chk[Q[i].l]=1;}
            if(!chk[Q[i].r]){A[++idx]=Q[i].r; chk[Q[i].r]=1;}
            if(!chk[Q[i].l+1]){A[++idx]=Q[i].l+1; chk[Q[i].l+1]=1;}
            if(!chk[Q[i].r+1]){A[++idx]=Q[i].r+1; chk[Q[i].r+1]=1;}
            if(!chk[Q[i].l-1]){A[++idx]=Q[i].l-1; chk[Q[i].l-1]=1;}
            if(!chk[Q[i].r-1]){A[++idx]=Q[i].r-1; chk[Q[i].r-1]=1;}
        }
        sort(A+1, A+idx+1); build(1, idx, 1);

        chk.clear(); chk[0]=1;
        for(int i=1; i<=N; ++i){
            qs=Q[i].l; qe=Q[i].r; K+=1;
            update(1, idx, 1);
        }
        query(1, idx, 1, st[1].v);
        printf("%d\n", vec.size());
        vec.clear();
    }
    return 0;
}
