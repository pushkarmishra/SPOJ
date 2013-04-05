/*
Algo: Segment Tree
Complexity: N*LogN
*/

#include <iostream>
#include<cstdio>
#define gc getchar_unlocked
using namespace std;
 
static int qs, qe;
struct s{int mod0, mod1, mod2, flip;} tree[500004];
 
void scan(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
 
inline void refresh(int node){
    int temp=tree[node].mod0;
    tree[node].mod0=tree[node].mod2;
    tree[node].mod2=tree[node].mod1;
    tree[node].mod1=temp;
}
 
int build(int x, int y, int node){
    if (x==y){
        tree[node].mod0=1;
        return tree[node].mod0;
    }
    int mid = (x+y)/2;
    tree[node].mod0 = build(x, mid, 2*node+1)
                         + build(mid+1, y, 2*node+2);
    return tree[node].mod0;
}
 
inline void update(int ss, int se, int node){
    if (qe<ss || se<qs || ss >se) return;
 
    else if (qs<=ss && se<=qe){
        refresh(node);
        tree[node].flip+=1;
        if (tree[node].flip>2) tree[node].flip-=3;
        return;
    }
    int mid=(ss+se)/2;
    update(ss, mid, 2*node+1); update(mid+1, se, 2*node+2);
 
    tree[node].mod0=tree[2*node+1].mod0+tree[2*node+2].mod0;
    tree[node].mod1=tree[2*node+1].mod1+tree[2*node+2].mod1;
    tree[node].mod2=tree[2*node+1].mod2+tree[2*node+2].mod2;
    
    if (tree[node].flip==1) refresh(node);
    else if (tree[node].flip==2){refresh(node); refresh(node);}
 
    return;
}
 
inline int query(int ss, int se, int node, int flips){
    if (qe<ss || se<qs) return 0;
 
    if (qs<=ss && se<=qe){
        if (flips==1) return tree[node].mod2;
        else if (flips==2) return tree[node].mod1;
        else return tree[node].mod0;
    }
    
    int mid=(ss+se)/2,
        countflip=(flips+tree[node].flip);
        if(countflip>2) countflip-=3;
    int a = query(ss, mid, 2*node+1, countflip),
        b = query(mid+1, se, 2*node+2, countflip);
 
    return a+b;
}
 
int main()
{
    int N, Q, in;
 
    scan(N); scan(Q);
    build(1, N, 1);
 
    for (int i=1; i<=Q; ++i){
        scan(in);
        if (in==0){
            scan(qs); scan(qe); qs++; qe++;
            update(1, N, 1);
        }
        
        else{
            scan(qs); scan(qe); qs++; qe++;
            int ans=query(1, N, 1, 0);
            cout << ans << '\n';
        }
    }
    return 0;
}
