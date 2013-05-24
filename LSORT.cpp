/*
Algo: Dynamic Programming and Binary Indexed Tree
Complexity: (N^2)*LogN
*/

#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAX 1002

static int BIT[MAX+1][MAX+1], N, T; long long DP[MAX+1][MAX+1];
struct s{int v, i;} A[1002];

int cmp(s const& l, s const& r){return l.v<r.v;}
inline void update(int r, int i, int v){
    for(; i<=MAX; i+=(i&-i)) BIT[r][i]+=v;
}
inline int query(int r, int i){
    int ans=0;
    for(; i>0; i-=(i&-i)) ans+=BIT[r][i];
    return ans;
}
inline void compute(){
    for (int i=0; i<=N-1; ++i){
        for (int j=1; j<=N; ++j){
            if(j+i>N) break;
            long long a, b, c, d;
            a=DP[j][j+i-1]; b=DP[j+1][j+i];
            c=(i+1)*(A[j+i].i-query(j, A[i+j].i-1));
            d=(i+1)*(A[j].i-query(j+1, A[j].i-1));
            DP[j][j+i]=std::min(a+c, b+d);
            update(j, A[i+j].i, 1);
        }
    }
}

int main()
{
    scanf("%d", &T);
    while(T--){
        memset(BIT, 0, sizeof BIT); scanf("%d", &N);
        for (int i=1; i<=N; ++i){
            scanf("%d", &A[i].v); A[i].i=i;
        }
        std::sort(A+1, A+N+1, cmp);
        for (int i=1; i<=N; ++i)DP[i][i]=A[i].i;
        compute(); printf("%lld\n", DP[1][N]);
    }
    return 0;
}
