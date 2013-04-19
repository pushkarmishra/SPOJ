/*
Algo: Sorting
Complexity: N
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
 
struct s{long time; int st;} record[500];
int cmp(s const& lhs, s const& rhs){
    return lhs.time<rhs.time;
}
 
int main()
{
    int T, N; scanf("%d", &T);
    while(T--){
        memset(record, 0, sizeof record);
        scanf("%d", &N);
        for(int i=1; i<=2*N; ++i){
            scanf("%ld", &record[i].time);
            record[i].st=(i%2==1)? 1:-1;
        }
        std::sort(record+1, record+(2*N)+1, cmp);
        
        int max=0, sum=0;
        for(int j=1; j<=2*N; ++j){
            sum+=record[j].st;
            if (sum>max) max=sum;
        }
        printf("%d\n", max);
    }
    return 0;
}
