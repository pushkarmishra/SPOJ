/*
Algo: Dynamic Programming
Complexity: N
*/

#include <cstring>
#include <cstdio>
const long long M= 1000000007;
 
static char in[100010]; int T;
static long long dp[256], ANS, pa;
 
int main(){
    scanf("%d", &T);
    while(T--){
        memset(dp, 0, sizeof dp);
        scanf("%s", in); ANS=1;
        for(int i=0; i<strlen(in); ++i){
            int t=in[i]-'A'; pa=ANS%M;
            ANS=((ANS%M)+(ANS%M))%M; ANS=((ANS%M)-(dp[t]%M))%M;
            dp[t]=pa;
        }
        printf("%lld\n", ANS);
    }
    return 0;
}
