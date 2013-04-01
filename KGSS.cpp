/*
Algo: Segment Tree
Complexity: N*LogN
*/

#include <iostream>
#include <algorithm>
using namespace std;

static long arr[100001], maxans1=0, maxans2=0;
struct s{long max1, max2;} tree[400004];

void getMAX(int ss, int se, int qs, int qe, int index)
{
    if (qs<=ss && qe>=se){
        if (tree[index].max1>maxans1){
            maxans2=maxans1; maxans1=tree[index].max1;
            (tree[index].max2>maxans2)? maxans2=tree[index].max2: maxans2=maxans2;
        }
        else if (tree[index].max1>maxans2) maxans2=tree[index].max1;
        return;
    }

    if (se<qs || ss>qe) return;

    int mid = (ss+se)/2;
    getMAX(ss, mid, qs, qe, 2*index+1);
    getMAX(mid+1, se, qs, qe, 2*index+2);
}

void construct(int x, int y, int s)
{
    if (x==y){
        tree[s].max1 = arr[x];
        return;
    }

    int mid = (x+y)/2; long temp[4];
    construct(x, mid, 2*s+1);
    construct(mid+1, y, 2*s+2);

    temp[0]=tree[2*s+1].max1; temp[1]=tree[2*s+1].max2;
    temp[2]=tree[2*s+2].max1; temp[3]=tree[2*s+2].max2;
    sort(temp, temp+4);

    tree[s].max1=temp[3]; tree[s].max2=temp[2];
}

void update(int ss, int se, int x, int val, int index)
{
    arr[x]=val;
    if (x>se || x<ss)return;

    if (ss==se){
        tree[index].max1=val;
        tree[index].max2=0;
    }

    if (ss!=se){
        int mid=(ss+se)/2; long temp[4];
        update(ss, mid, x, val, 2*index+1);
        update(mid+1, se, x, val, 2*index+2);
        temp[0]=tree[2*index+1].max1; temp[1]=tree[2*index+1].max2;
        temp[2]=tree[2*index+2].max1; temp[3]=tree[2*index+2].max2;
        sort(temp, temp+4);

        tree[index].max1=temp[3]; tree[index].max2=temp[2];
    }
}

int main()
{
    ios::sync_with_stdio(0);

    int N, Q, x, y; char in;

    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> arr[i];
    construct(1, N, 1);

    cin >> Q;
    for (int i = 1; i<= Q; ++i){
        maxans1=maxans2=0;
        cin >> in >> x >> y;

        if (in=='U') update(1, N, x, y, 1);

        else if (in=='Q'){
            getMAX(1, N, x, y, 1);
            cout << maxans1+maxans2 << endl;
        }
    }

    return 0;
}
