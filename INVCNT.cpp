/*
Algorithm: Binary Indexed Tree
Complexity: O(n*Log n)
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 200010
 
static int N;
long long read(vector<long long> &tree, int idx)
{
    long long sum = 0;
    for(; idx>0; idx-=(idx&-idx))
        sum += tree[idx];
    return sum;
}
void update(vector<long long> &tree, int idx, long long val)
{
    for (; idx<=N; idx+=(idx&-idx))
        tree[idx] += val;
}
 
int main()
{
    cin.sync_with_stdio(0); cout.sync_with_stdio(0);
    
    int T; cin >> T;
    while(T--)
    {
        vector<long long> tree(MAX), A(MAX), B(MAX);
        long long invcnt=0;
        cin >> N;
        
        for (int i=0; i < N; ++i)
        {
            cin >> A[i];
            B[i] = A[i];
        }
        
        sort(B.begin(), B.begin()+N);
        
        for (int i = 0; i < N; ++i)
        {
            vector<long long>::iterator rank;
            rank = lower_bound(B.begin(), B.begin()+N, A[i]);
            A[i] = (rank-B.begin())+1;
        }
        
        for (int i = N-1; i >= 0; --i)
        {
            long long x = read(tree, A[i]-1);
            invcnt+=x;
            update(tree, A[i], 1);
        }
        cout << invcnt << '\n';
    }
    return 0;
}
