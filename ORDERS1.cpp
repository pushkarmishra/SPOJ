/*
Algo: Square Root Decomposition
Complexity: N + sqrt(N)
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
#define gc getchar_unlocked

void scan(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
 
static int arr[200001], result[200001], ANS[200001], indices[500], arr2[500][500];

int main()
{
    ios::sync_with_stdio(0);
    
    int T; scan(T);
    while(T--){
        int n, k = 0, d, r, s, sum, temp, m, diff, check = 1, num=1;
        scan(n);
        d = sqrt(n) + 1;
 
        for (int i = 0; i < n; i++) scan(arr[i]);
        memset(indices, 0, sizeof indices); memset(arr2, 0, sizeof arr);
 
        for (r = 0; r < d; r++){
            for (s = 0; s < d; s++){
                arr2[r][s] = num++;
                if (num == n+1){
                    check = 0; break;
                }
            }
            if (!check) break;
        }
 
        int l = s;
        while (l >= 0){
            arr2[r][d-1-k] = arr2[r][l];
            k = k++; l--;
        }
 
        k = d-1 - k + 1;
        for (int t = 0; t < k; t++)arr2[r][t] = 0;
 
        indices[r] = indices[r] + k;
 
        for (int i = n-1; i >= 0; i--){
            sum = 0; m = 0;
            while (sum < arr[i] + 1) sum +=(d-indices[m++]);

            m--;
            sum =sum-(d - indices[m]);
            diff = arr[i] + 1 - sum;
            temp = indices[m] + diff - 1;
 
            result[arr2[m][temp] - 1] = i+1;
            for (int w = temp - 1; w >= indices[m]; w--)
                arr2[m][w+1] = arr2[m][w];
        
            arr2[m][indices[m]] = 0;
            indices[m]++;
        }
 
        for (int p = n-1; p >= 0; p--) ANS[result[p]]=n-p;
        for (int p=1; p <= n; p++) cout << ANS[p] << ' ';
        cout << '\n';
    }
    return 0;
}
