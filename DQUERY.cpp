/*
Algorithm: Binary Indexed Tree
Complexity: O((N+Q)*logN)
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define MAX 30010
 
static int tree[MAX], arr[1500000];
 
struct str1{int s, f, rank;} A[1500000];
struct str2{int a, rank;} B[1500000];
 
inline void update(int idx, int val)
{
    for (; idx < MAX; idx+=(idx&-idx))
        tree[idx]+=val;
}
 
inline int read(int idx)
{
    int ans=0;
    for (; idx > 0; idx-=(idx&-idx))
        ans+=tree[idx];
    return ans;
}
 
int comp1(str1 const& lhs, str1 const& rhs)
{
    if (lhs.f==rhs.f)
    {
        if (lhs.rank!=0 && rhs.rank!=0) return lhs.s<rhs.s;
        else if(lhs.rank==0) return 1;
        else if (rhs.rank==0)return 0;
    }
    else return lhs.f<rhs.f;
}
 
int comp2(str2 const& lhs, str2 const& rhs)
{return lhs.rank<rhs.rank;}
 
int main()
{
    cin.sync_with_stdio(0); cout.sync_with_stdio(0);
    
    int N, Q, in1, in2, i=1, k=1;
    cin >> N;
    for (i = 1; i <= N; ++i)
    {
        cin >> in1;
        A[i].s=arr[in1];
        A[i].f=arr[in1]=i;
    }
    cin >> Q;
    for (; i<=N+Q; ++i)
    {
        cin >> in1 >> in2;
        A[i].f=in2; A[i].s=in1;
        A[i].rank=i-N;
    }
 
    sort(A+1, A+N+Q+1, comp1);
    
    for (int j=1; j<=N+Q; ++j)
    {
        if(A[j].rank==0)
        {
            update(A[j].f, 1);
            if (A[j].s!=0)update(A[j].s, -1);
        }
        else
        {
            B[k].a=read(A[j].f)-read(A[j].s-1);
            B[k++].rank=A[j].rank;
        }
    }
    
    sort(B+1, B+k, comp2);
    for (int p=1; p < k; p++)
        cout << B[p].a << '\n';
    return 0;
}
