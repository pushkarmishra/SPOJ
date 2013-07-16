/*
Algo: Fast Fourier Transform and Polynomial Multiplication
Complexity: NLogN
*/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

#define PI 3.141592653589793238462
#define REP(i,a,b) for(int i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)

typedef struct struct_point{double x,y;}pnt;
pnt P[300000], Q[300000];

pnt pntPlus(pnt a,pnt b){a.x+=b.x; a.y+=b.y; return a;}
pnt pntMinus(pnt a,pnt b){a.x-=b.x; a.y-=b.y; return a;}
pnt pntMultiple(pnt a,pnt b){pnt c; c.x=a.x*b.x-a.y*b.y; c.y=a.x*b.y+a.y*b.x; return c;}
pnt pntMultipleDouble(pnt a,double k){a.x*=k; a.y*=k; return a;}
pnt pntPolar(double r,double t){pnt a; a.x=r*cos(t); a.y=r*sin(t); return a;}
pnt pntGenerator(double x,double y){pnt res; res.x=x; res.y=y; return res;}

void fft(int n, double theta, pnt a[]){
    int i, j, k, m, mh; pnt w, x;

    for(m=n; m>=2; m/=2){
        mh = m / 2;
        rep(i,mh){
            w = pntPolar(1, i*theta);
            for(j=i; j<n; j+=m){
                k = j+mh;
                x = pntMinus(a[j], a[k]);
                a[j] = pntPlus(a[j], a[k]);
                a[k] = pntMultiple(w, x);
            }
        }
        theta *= 2;
    }
    i = 0;
    REP(j,1,n-1){
        for(k=n/2; k > (i ^= k); k/=2);
        if(j < i) w=a[i], a[i]=a[j], a[j]=w;
    }
}

int main(){
    int mrk[300000]; char s[100010]; scanf("%s", s);
    int f[300000], sum=strlen(s);
    for(int i=0; i<strlen(s); ++i)mrk[i]=s[i]-96;
    int L=log2(2*sum); L=pow(2,L+1); double invN2 = 1.0/L;

    for(int i=0; i<=L; ++i){
        if(mrk[i]==1){
            P[i]=pntGenerator(1, 0);
            Q[sum-1-i]=pntGenerator(1, 0);
        }
    }
    fft(L, 2*PI*invN2, P); fft(L, 2*PI*invN2, Q);
    rep(i, L) P[i]=pntMultiple(P[i], Q[i]);
    fft(L,-2*PI*invN2, P);
    rep(i, L) P[i].x*=invN2;
    for(int i=1; i<sum;++i)f[i]=(long long)(P[sum-1+i].x+0.5);

    for(int i=0; i<=L; ++i)P[i]=Q[i]=pntGenerator(0, 0);
    for(int i=0; i<=L; ++i){
        if(mrk[i]==2){
            P[i]=pntGenerator(1, 0);
            Q[sum-1-i]=pntGenerator(1, 0);
        }
    }
    fft(L, 2*PI*invN2, P); fft(L, 2*PI*invN2, Q);
    rep(i, L) P[i]=pntMultiple(P[i], Q[i]);
    fft(L,-2*PI*invN2, P);
    rep(i, L) P[i].x*=invN2;
    for(int i = 0;i<sum;++i)f[i]+=(long long)(P[sum-1+i].x+0.5);

    for(int i=0; i<=L; ++i)P[i]=Q[i]=pntGenerator(0, 0);
    for(int i=0; i<=L; ++i){
        if(mrk[i]==3){
            P[i]=pntGenerator(1, 0);
            Q[sum-1-i]=pntGenerator(1, 0);
        }
    }
    fft(L, 2*PI*invN2, P); fft(L, 2*PI*invN2, Q);
    rep(i, L) P[i]=pntMultiple(P[i], Q[i]);
    fft(L,-2*PI*invN2, P);
    rep(i, L) P[i].x*=invN2;
    for(int i = 0;i<sum;++i)f[i]+=(long long)(P[sum-1-i].x+0.5);

    int best=-1, ind;
    for(int i=1; i<sum; ++i)if(f[i]>best)best=f[i];
    for(int i=1; i<sum; ++i)if(f[i]==best)ind=i;
    printf("%d\n%d\n", best, ind);
    return 0;
}
