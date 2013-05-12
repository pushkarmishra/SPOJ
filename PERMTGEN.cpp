/*
Algo: Binary Search Tree
Complexity: N*LogN
*/

#include <cstdio>

int idx=0, t=1, N; static long long ANS[100010], V;
struct node{long long v; int ls, rs, i, s; node* l; node* r;};
int p;

inline node* bstin(node *n){
    if (n==NULL){
        n = new node; n->i=t; n->ls=0;
        n->l=NULL; n->r=NULL; n->v=V;
        n->rs=-idx; return n;
    }
    else if((n->v)+(n->ls)+(n->rs)+idx >= V){
        (n->ls)+=1; p=(n->i); n->l=bstin(n->l);
    }
    else{
        idx+=(n->ls)+1; p=(n->i); n->r=bstin(n->r);
    }
}
inline node* query(node *&n){
    if (n->l!=NULL) return query(n->l);
    if(n->r!=NULL) {idx+=(n->ls)+1; return query(n->r);}
    ANS[n->i]= n->ls+n->v+n->rs+idx;
    n=NULL; return n;
}

int main()
{
    scanf("%d%lld", &N, &V);
    node *root=NULL;
    root = bstin(root);
    for(int i=2; i<=N; ++i){
        scanf("%lld", &V); t=i;
        idx=0; bstin(root);
    }

    for (int i=1; i<=N; ++i) {idx=0; query(root);}
    for (int i=1; i<=N; ++i) printf("%lld ", ANS[i]);
    return 0;
}
