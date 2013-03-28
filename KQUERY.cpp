/*
Algo: Binary Indexed Tree
Complexity: (N+Q)*Log(N+Q)
*/
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXQ 262144
#define MAX 32768
 
struct q
{
    int s, e, rank; long long k;
} query[MAXQ+1], ans[MAXQ+1];
 
static int tree[MAX+1], N, Q;
 
inline void update(int idx, int val)
{
    for (; idx<=MAX; idx+=(idx & -idx))
        tree[idx]+= val;
}
 
inline int read(int idx)
{
    int answer=0;
    for (; idx>0; idx-=(idx & -idx))
        answer+=tree[idx];
    return answer;
}
 
int cmp(q const& lhs, q const& rhs) 
{
    if (lhs.k==rhs.k)
        return (lhs.rank==0)? 0: 1;
    else return lhs.k>rhs.k;
}
 
int main()
{
    ios::sync_with_stdio(0);
 
    cin >> N;
    for (int i=1; i <= N; ++i){
        cin >> query[i].k; query[i].e=i;
    }
    cin >> Q;
    for (int i = N+1; i <= N+Q; ++i){
        cin >> query[i].s >> query[i].e >> query[i].k;
        query[i].rank=N-i;
    }
    sort(query+1, query+N+Q+1, cmp);
    
    int temp=1;
    for (int t = 1; t<=N+Q; ++t){
        if (query[t].rank==0) update(query[t].e, 1);
        else{
            ans[temp].k=query[t].rank;
            ans[temp++].e=read(query[t].e)-read(query[t].s-1);
        }
    }
    
    sort(ans+1, ans+Q+1, cmp);
    for (int i=1; i<=Q; ++i) cout << ans[i].e << '\n';
    return 0;
}
