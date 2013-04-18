/*
Algo: Segment Tree
Complexity: N*LogN
*/

include <cstdio>
#include <algorithm>
using namespace std;
 
static long long A[50001], y; int N, M, qs, qe, x, in;
struct segtree{long long ls, rs, bs, sum;} st[300004], temp, ans;
 
void construct(int x, int y, int idx){
    if (x==y){
        st[idx].sum=st[idx].ls=st[idx].rs=st[idx].bs=A[x];
        return;
    }
    int mid=(x+y)/2;
    construct(x, mid, 2*idx+1); construct(mid+1, y, 2*idx+2);
 
    st[idx].sum=st[2*idx+1].sum+st[2*idx+2].sum;
    st[idx].bs=max(max(st[2*idx+1].bs, st[2*idx+2].bs), st[2*idx+1].rs+st[2*idx+2].ls);
    st[idx].ls=max(st[2*idx+1].ls, st[2*idx+1].sum+st[2*idx+2].ls);
    st[idx].rs=max(st[2*idx+2].rs, st[2*idx+2].sum+st[2*idx+1].rs);
}
 
void modify(int ss, int se, int idx){
    if (x>se || x<ss)return;
    if(ss==se){
        st[idx].bs=st[idx].ls=st[idx].rs=st[idx].sum=y;
        return;
    }
    if(ss!=se){
        int mid=(ss+se)/2;
        modify(ss, mid, 2*idx+1); modify(mid+1, se, 2*idx+2);
 
        st[idx].sum=st[2*idx+1].sum+st[2*idx+2].sum;
        st[idx].bs=max(max(st[2*idx+1].bs, st[2*idx+2].bs), st[2*idx+1].rs+st[2*idx+2].ls);
        st[idx].ls=max(st[2*idx+1].ls, st[2*idx+1].sum+st[2*idx+2].ls);
        st[idx].rs=max(st[2*idx+2].rs, st[2*idx+2].sum+st[2*idx+1].rs);
    }
}
 
void query(segtree &ans, int ss, int se, int idx){
    if (se<qs || ss>qe) {ans=temp; return;}
    if (ss>=qs && qe>=se) {ans=st[idx]; return;}
 
    int mid=(ss+se)/2;
    segtree left, right;
    query(left, ss, mid, 2*idx+1);
    query(right, mid+1, se, 2*idx+2);
 
    ans.sum=left.sum+right.sum;
    ans.bs=max(max(left.bs, right.bs), left.rs+right.ls);
    ans.ls=max(left.ls, left.sum+right.ls);
    ans.rs=max(right.rs, right.sum+left.rs);
}
 
int main()
{
    scanf("%d", &N);
    for (int i = 1; i<= N; ++i) scanf("%lld", &A[i]);
    temp.bs=temp.ls=temp.rs=temp.sum=-999999999;
    construct(1, N, 1);
 
    scanf("%d", &M);
    for (int i = 1; i<= M; ++i){
        scanf("%d", &in);
        if (!in){
            scanf("%d %lld", &x, &y);
            A[x]=y; modify(1, N, 1);
        }
        else{
            scanf("%d %d", &qs, &qe);
            query(ans, 1, N, 1);
            printf("%lld\n", ans.bs);
        }
    }
    return 0;
}
