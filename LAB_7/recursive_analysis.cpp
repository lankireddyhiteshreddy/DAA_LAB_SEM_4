#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
 
int matrixChainRec(vector<int> &arr, int i, int j) {
    if (i == j) 
        return 0;
     
    int minCost = INT_MAX;
     
    for (int k = i; k < j; k++) {
        int cost = matrixChainRec(arr, i, k) + matrixChainRec(arr, k + 1, j) + arr[i - 1] * arr[k] * arr[j];
        minCost = min(minCost, cost);
    }
 
    return minCost;
}
 
int main() {
    srand(time(NULL));
 
    for(int n = 1;n<=20;n+=1){
        vector<int> dim(n+1);
        for (int i = 0; i <= n; i++) {
            dim[i] = rand()%10+1;
        }    
        auto start = high_resolution_clock::now();
        int minCost = matrixChainRec(dim, 1, n);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout <<n<<","<<duration.count()<<endl;
    }
    return 0;
}