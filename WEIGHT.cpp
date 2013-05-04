/*
Algo: DP/AD HOC
Complexity: N
*/

#include <cstdio>
#include <cstring>
using namespace std;
 
static long A[1000001], N;
 
int main()
{
    int T; scanf("%d", &T);
    while(T--){
        memset(A, 0, sizeof A);
        scanf("%ld", &N); long long s=0, ANS=0, ANS1=0; 
        for (int i=N; i>=1; --i) scanf("%ld", &A[i]);
        
        for (int i=1; i<N; ++i){
            s += A[i];
            ANS1 += A[i]+s;
            if (s<0){
                ANS+=ANS1;
                ANS1=s=0;
            }
        }
        printf("%lld\n", ANS+ANS1+A[N]);
    }
}
