/*
Algo: Binary Indexed Tree
Complexity: N*LogN
*/

#include <cstdio>
#include <cstring>
using namespace std;
#define MAX 20500
#define init(Arr) memset((Arr), 0, sizeof (Arr))
 
static int BIT[MAX+1], ANS[MAX], N, T;
inline void update(int i, int v){
    for (; i<=MAX; i+=(i & -i)) BIT[i]+=v;
}
inline int query(int i){
    int ans=0;
    for (; i>0; i-=(i & -i)) ans+=BIT[i];
    return ans;
}
 
int main()
{
    scanf("%d", &T);
    while(T--){
        init(BIT); init(ANS);
        scanf("%d", &N);
        for (int i=1; i<=N; ++i) update(i, 1);
        int M=N, L=1, s, e;
        
        for(int i=1; i<=N; ++i){
            L= (L+i)%M;
            L= (!L)? M: L; M--;
            
            s=1; e=N;
            while(s<=e){
                int mid = (s+e)>>1;
                if (query(mid)>=L) e=mid-1;
                else if (query(mid)<L) s=mid+1;
            }
            ANS[s]=i; update(s, -1);
        }
        for(int i=1; i<=N; ++i) printf("%d ", ANS[i]);
        printf("\n");
    }
    return 0;
}
