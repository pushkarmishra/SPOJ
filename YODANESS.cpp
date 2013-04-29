/*
Algo: Binary Indexed Tree
Complexity: N*LogN
*/

#include <iostream>
#include <cstring>
#include <map>
using namespace std;
#define MAX 32000

string yoda[30001], sen[30001];
static int BIT[MAX+1], N, T, ANS;
map <string, int> m;

inline void update(int i){
    for(; i<=MAX; i+=(i&-i)) BIT[i]++;
}

inline int query(int i){
    int ans=0;
    for(; i>0; i-=(i&-i)) ans+=BIT[i];
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);

    cin >> T;
    while(T--){
        memset(BIT, 0, sizeof BIT);
        cin >> N; ANS=0;
        for(int i=1; i<=N; ++i) cin >> yoda[i];
        for(int i=1; i<=N; ++i) {cin >> sen[i]; m[sen[i]]=i;}

        for(int i=1; i<=N; ++i){
            int idx=m[yoda[i]];
            ANS+= (query(MAX)-query(idx));
            update(idx);
        }
        cout << ANS << '\n';
    }
    return 0;
}
