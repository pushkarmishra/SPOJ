/*
Algo: Recursion and Dynamic Programming
Complexity: N
*/

#include <cstdio>
using namespace std;
 
long long coins = 0;
static long long coin[10000001];
 
long long calc(long long n){
    if (n < 10000001)
        coins += coin[n];
    else if (n >= (n/2)+(n/3)+(n/4))
        coins += n;
    else
        coins += (calc(n/2)+calc(n/3)+calc(n/4));
    
    return 0;
}
 
int main()
{
    long long N;
    coin[0] = 0; coin[1] = 1; coin [2] = 2;
    for (int i = 3; i < 10000001; i++)
        (i >= (coin[i/2]+coin[i/3]+coin[i/4]))? coin[i] = i: coin[i] = (coin[i/2]+coin[i/3]+coin[i/4]);
    while (scanf("%lld", &N) != EOF){
        coins = 0;
        calc(N);
        printf("%lld\n", coins);
    }
    return 0;
}
