/*
INCSEQ and ELDORADO
Algo: Binary Indexed Tree
Complexity: N*LogN
*/

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAX 32768
 
static long long bitdp[101][32769];
 
inline void update (int k, int idx, long val)
{
    for (; idx <= MAX; idx+=(idx&-idx))
        bitdp[k][idx] += val;
}
 
inline long long sum (int k, int idx)
{
    long long ans=0;
    for (; idx > 0; idx-=(idx&-idx))
        ans += bitdp[k][idx];
    return ans;
}
 
int main()
{
    int N, K, in; long long temp;
    
    scanf("%d %d", &N, &K);
    while (N>0 && K>0)
    {
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d", &in); in+=10001;
            for (int j = 1; j <= K; ++j)
            {
                if (j==1) update(j, in, 1);
                else
                {
                    temp=sum(j-1, in-1);
                    update(j, in, temp);
                }
            }
        }
        printf("%lld\n", bitdp[K][MAX]);
        
        scanf("%d %d", &N, &K);
        memset(bitdp, 0, sizeof(bitdp));
    }
    
    return 0;
}
