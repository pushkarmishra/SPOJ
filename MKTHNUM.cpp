/*
Algo: Mergesort Tree and Binary Search
Complexity: NLogN + M(LogN)^3
*/

#include <cstdio>

static int A[100010], B[100010], *st[500000], val;
static int N, M, K, qs, qe, idx; int *P[100010];

void merge(int i, int j, int m, int n){
    int *p=new int[j-i+2];
    int k=m+1, l=i, q=i, s=i;
    while (i<=m && k<=j)
        B[l++]=(A[i]<A[k])? A[i++]: A[k++];
    while (k<=j) B[l++]=A[k++];
    while (i<=m) B[l++]=A[i++];
    for (;q<=j; q++) A[q]=p[q-s+1]=B[q];
    p[0]=j-s+1; st[n]=p;
}
void mergesort(int i, int j, int n){
    if (i < j){
       int m=(i+j)/2;
       mergesort(i, m, 2*n+1);
       mergesort(m+1, j, 2*n+2);
       merge(i, j, m, n);
    }
    else if(i==j){
        int *p=new int[2];
        p[0]=1; p[1]=A[i]; st[n]=p;
    }
}
inline void query(int x, int y, int n){
    if(y<qs || qe<x) return;
    if(qs<=x && y<=qe){P[++idx]=st[n]; return;}
    int m=(x+y)>>1;
    query(x, m, 2*n+1); query(m+1, y, 2*n+2);
}

int main()
{
    scanf("%d %d", &N, &M); int ans, p, q;
    for(int i=1; i<=N; ++i) scanf("%d", &A[i]);
    mergesort(1, N, 1);
    while(M--){
        scanf("%d %d %d", &qs, &qe, &K);
        idx=0; query(1, N, 1);
        for (int i=1; i<=idx; ++i){
            p=1, q=P[i][0];
            while(p<=q){
                int mid=(p+q)>>1; val=P[i][mid]; ans=0;
                for(int j=1; j<=idx; ++j){
                    int s=1, e=P[j][0];
                    while(s<=e){
                        int m=(s+e)>>1;
                        if(val<=P[j][m]) e=m-1;
                        else s=m+1;
                    }
                    ans+=s-1;
                }
                if (ans+1==K) break;
                if(ans+1>K)q=mid-1;
                else p=mid+1;
            }
            if(ans+1==K){printf("%d\n", val); break;}
        }
    }
    return 0;
}
