/*
Algo: Binary Indexed Tree
Complexity: N*LogN
*/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 50010
 
static int BIT[MAX+1], N, M;
long long ANS[MAX+1], Time=0, RR=0;
struct str{long long t; int i;} A[MAX+1];
vector<int> p;
 
inline void update(int i, int v){
    for (; i<=MAX; i+= (i&-i)) BIT[i]+=v;
}
inline int query(int i){
    int ans=0;
    for (; i>0; i-= (i&-i)) ans+=BIT[i];
    return ans;
}
int cmp(str const& lhs, str const& rhs) {return lhs.t<rhs.t;}
 
int main()
{
    scanf("%d", &N); M=N;
    for (int i=1; i<=N; ++i){
        scanf("%lld", &A[i].t);
        A[i].i=i;
        update(i, 1);
    }
    stable_sort(A+1, A+N+1, cmp);
 
    for(int i=1; i<=N; ++i){
        if(RR+1 >= A[i].t){
            int v=A[i].i;
            ANS[v]=Time+query(v);
            p.push_back(v);
        }
        else{
            for(int k=0; k<p.size(); ++k) update(p[k], -1);
            p.clear();
 
            Time += M; RR+=1; M=query(MAX);
            Time += (A[i].t-RR-1)*M;
            RR = A[i--].t-1;
        }
    }
 
    for (int i=1; i<=N; ++i) printf("%lld\n", ANS[i]);
    return 0;
}
