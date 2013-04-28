/*
Algo: Binary Indexed Tree and Binary Search
Complexity: N*LogN
*/

#include <cstdio>
using namespace std;
#define MAX 200010

static int BIT[MAX+1], INV[200001], N, ANS[200001], L, s, e, T;

void update(int i, int v){
    for(; i<=MAX; i+=(i&-i)) BIT[i]+=v;
}

inline int query(int i){
    int ans=0;
    for(; i>0; i-=(i&-i)) ans+=BIT[i];
    return ans;
}

int main()
{
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        for(int i=1; i<=N; ++i){
            scanf("%d", &INV[i]); update(i, 1);
        }

        for(int i=N; i>=1; --i){
            L=i-INV[i]; s=1; e=N;
            while(s<=e){
                int mid=(s+e)/2;
                if(query(mid)<L) s=mid+1;
                else if (query(mid)>=L) e=mid-1;
            }
            ANS[i]=s;
            update(s, -1);
        }
        for(int i=1; i<=N; ++i) printf("%d ", ANS[i]);
        printf("\n");
    }
    return 0;
}
