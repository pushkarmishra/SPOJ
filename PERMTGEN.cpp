/*
Algo: Mergesort Tree and Binary Indexed Tree
Complexity: N*LogN*LogN
*/

#include <vector>
#include <cstdio>
using namespace std;
 
struct s{long long v; int i;} A[100010], B[100010];
int N, s, e; long long C[100010];
 
inline void update(vector<int> &p, int i){
    for(; i<p.size(); i+=(i&-i))p[i]++;
}
inline int query(vector<int> &p, int i){
    int ans=0;
    for(; i>0; i-=(i&-i))ans+=p[i];
    return ans;
}
inline void merge(int i, int m, int k){
    vector<int> q(m-i+3);
    for (int j=m+1; j<=k; ++j){
        int s=i, e=m;
        while(s<=e){
            int m=(s+e)>>1;
            if(query(q, m-i+1)+A[m].v>=C[j])e=m-1;
            else s=m+1;
        }
        update(q, s-i+1);
    }
    int t=m+1, l=i, p=i;
    while(i<=m && t<=k){
        if(A[i].v+query(q, i-p+1)<A[t].v){
            A[i].v+=query(q, i-p+1);
            B[l++]=A[i++];
        }
        else B[l++]=A[t++];
    }
    while(i<=m){
        A[i].v+=query(q, i-p+1); B[l++]=A[i++];
    }
    while(t<=k) B[l++]=A[t++];
    for(; p<=k; ++p)A[p]=B[p];
}
void divsol(int i, int j){
    if (i < j){
       int mid = (i+j)>>1;
       divsol(i, mid); divsol(mid+1, j);
       merge(i, mid, j);
    }
}
 
int main()
{
    scanf("%d", &N);
    for (int i=1; i<=N; ++i){
        scanf("%lld", &A[i].v);
        C[i]=A[i].v; A[i].i=i;
    }
    divsol(1, N);
    for (int i=1; i<=N; ++i) C[A[i].i]=A[i].v;
    for (int i=1; i<=N; ++i) printf("%lld ", C[i]);
    return 0;
}
