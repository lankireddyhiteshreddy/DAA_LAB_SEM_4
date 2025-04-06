#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
 
int matrixChainDP(vector<int> arr, int n,vector<vector<int>>& dp) {
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX; 
 
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
 
    return dp[1][n - 1];
}
 
int main() {
    srand(time(NULL));
 
    for(int n = 1;n<=20;n+=1){
        vector<int> dim(n+1);
        for (int i = 0; i <= n; i++) {
            dim[i] = rand()%10+1;
        }    
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        auto start = high_resolution_clock::now();
        int minCost = matrixChainDP(dim, n+1 , dp);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout <<n<<","<<duration.count()<<endl;
    }
    return 0;
}