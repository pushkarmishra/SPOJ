/*
Algo: Binary Indexed Tree
Complexity: N*LogN
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAX 200010
 
static int BIT[MAX+1], ANS[MAX+1], N, M;
struct str{long s, e, i;} A[MAX+1];
static long S[400020];
 
int bsearch(long v){
    int i=1, j=M;
    while(i<=j){
        int mid=(i+j)>>1;
        if(S[mid]>=v) j=mid-1;
        else i=mid+1;
    }
    return i;
}
inline void update(int i){
    for (; i<=MAX; i+=(i&-i)) BIT[i]++;
}
inline int query(int i){
    int ans=0;
    for (; i>0; i-=(i&-i)) ans+=BIT[i];
    return ans;
}
int cmp(str const& lhs, str const& rhs){
    return (lhs.s==rhs.s)? lhs.e>rhs.e: lhs.s<rhs.s;
}
 
int main()
{
    while(scanf("%d", &N)==1){
        memset(BIT, 0, sizeof BIT); M=0; int k;
        for (int i=1; i<=N; ++i){
            scanf("%ld %ld", &A[i].s, &A[i].e);
            A[i].i=i;
            S[++M]=A[i].e;
        }
        sort(S+1, S+M+1);
        sort(A+1, A+N+1, cmp);
 
        for (int i=1; i<=N; ++i){
            int t=bsearch(A[i].e);
            int temp = query(MAX)-query(t-1);
            if (A[i].s==A[i-1].s && A[i].e==A[i-1].e){
                k++; ANS[A[i].i]=temp-k;
            }
            else{
                k=0; ANS[A[i].i]=temp;
            }
            update(t);
        }
        
        for (int i=1; i<=N; ++i) printf("%d ", ANS[i]);
        printf("\n");
    }
    return 0;
}
