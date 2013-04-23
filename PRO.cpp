/*
Algo: Binary Heap
Complexity: N*LogN
*/

#include <cstdio>
using namespace std;
 
static long mxh[4000000], mnh[4000000], count[1000010], in;
int imax=0, imin=0, N, K; long long ANS; long a, b;
 
inline void maxheapify(int i){
    if (i>1){
        int j=i/2;
        if(mxh[j]<mxh[i]){
            long temp=mxh[j]; mxh[j]=mxh[i]; mxh[i]=temp;
            maxheapify(j);
        }
    }
}
 
inline void minheapify(int i){
    if (i>1){
        int j=i/2;
        if(mnh[j]>mnh[i]){
            long temp=mnh[j]; mnh[j]=mnh[i]; mnh[i]=temp;
            minheapify(j);
        }
    }
}
 
inline void mindown(int i){
    int j; long temp;
    if (2*i<imin && (mnh[i]>mnh[2*i] || mnh[i]>mnh[2*i+1]))
        j=(mnh[2*i]<mnh[2*i+1])? 2*i: 2*i+1;
    else if(2*i==imin && mnh[i]>mnh[2*i]) j=2*i; 
    else return;
    
    temp=mnh[i]; mnh[i]=mnh[j]; mnh[j]=temp;
    mindown(j);
}
 
inline void maxdown(int i){
    int j; long temp;
    if (2*i<imax && (mxh[i]<mxh[2*i] || mxh[i]<mxh[2*i+1]))
        j=(mxh[2*i]>mxh[2*i+1])? 2*i: 2*i+1;
    else if(2*i==imax && mxh[i]<mxh[2*i]) j=2*i;
    else return;
    
    temp=mxh[i]; mxh[i]=mxh[j]; mxh[j]=temp;
    maxdown(j);
}
 
int main()
{
    scanf("%d", &N);
    while(N--){
        scanf("%d", &K);
        while(K--){
            scanf("%ld", &in); count[in]++;
            mnh[++imin]=mxh[++imax]=in;
            maxheapify(imax); minheapify(imin);
        }
        if (count[mxh[1]]>0) {a=mxh[1]; count[mxh[1]]--;}
        else{
            while(count[mxh[1]]<=0){
                mxh[1]=mxh[imax--]; maxdown(1);
            }
            a=mxh[1]; count[mxh[1]]--;
        }
        if (count[mnh[1]]>0) {b=mnh[1]; count[mnh[1]]--;}
        else{
            while(count[mnh[1]]<=0){
                mnh[1]=mnh[imin--]; mindown(1);
            }
            b=mnh[1]; count[mnh[1]]--;
        }
        
        ANS+= (a-b);
        mnh[1]=mnh[imin--]; mxh[1]=mxh[imax--];
        mindown(1); maxdown(1);
    }
    printf("%lld\n", ANS);
    return 0;
}
