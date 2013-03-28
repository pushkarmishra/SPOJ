/*
Algo: Binary Indexed Tree
Complexity: N*LogN
*/
#include <iostream>
#include <cstring>
using namespace std;
#define MAX 100200

static long long tree[MAX+1][2];
inline void update(int idx, long long val){
    for (int p=idx; p<=MAX; p+=(p & -p)){
        tree[p][0]+=val*(p-idx+1);
        tree[p][1]+=val;
    }
}

inline long long sum(int idx){
    long long res=0;
    for (int p=idx; p>0; p-=(p & -p)){
        res+=tree[p][0];
        res+=tree[p][1]*(idx-p);
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    
    int T, in, p, q; long v; cin >> T;
    while(T--){
        memset(tree, 0, sizeof(tree));
        int N, C;
        cin >> N >> C;
        
        for (int i=1; i<=C; i++){
            cin >> in;
            if (in==0){
                cin >> p >> q >> v;
                update(p, v); update(q+1, -v);
            }
            else if (in){
                cin >> p >> q;
                cout << sum(q)-sum(p-1) << '\n';
            }
        }
    }
    
    return 0;
}
