/*
Algo: Josephus Problem (Dynamic Programming)
Complexity: N
*/

#include <cstdio>
 
int main()
{
    int N, K, ANS=0;
 
    while (1){
        scanf("%d %d", &N, &K); ANS=0;
        if (!N && !K) break;
        for (int i = 1; i < N; i++)
            ANS = (ANS + K) % (i + 1);
        printf("%d %d %d\n", N, K, ANS+1);
    }
    return 0;
}
