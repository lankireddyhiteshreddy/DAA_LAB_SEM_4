#include <bits/stdc++.h>
using namespace std;
 
void paranthesise(vector<vector<int>> &temp,int i,int j,vector<vector<int>>& split){
    if(i==j || abs(i-j)==1) return;
    temp[i][0]+=1;
    temp[split[i][j]][1]+=1;
    if(split[i][j]+1<split.size()) temp[split[i][j]+1][0]+=1;
    temp[j][1]+=1;
    paranthesise(temp,i,split[i][j],split);
    paranthesise(temp,split[i][j]+1,j,split);
}
 
int matrixChainDP(int arr[], int n, vector<vector<int>>& split) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
 
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
 
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
    for(int i=0;i<n;i+=1){
        for(int j=0;j<n;j+=1) cout<<dp[i][j]<<" ";
        cout<<endl;
    }
    return dp[1][n - 1];
}
 
int main() {
    int n;
    cout << "Enter the number of matrices: ";
    cin >> n;
 
    int arr[n + 1];
    cout << "Enter the dimensions array: ";
    for (int i = 0; i <= n; i++) {
        cin >> arr[i];
    }
    vector<vector<int>> split(n+1, vector<int>(n+1, -1));
 
    int minCost = matrixChainDP(arr, n + 1,split);
    cout << "Minimum number of multiplications (DP): " << minCost << endl;
    vector<vector<int>> temp(n+1,vector<int>(2,0));
    paranthesise(temp,1,n,split);
    for(int i=1;i<=n;i+=1){
        for(int j=0;j<temp[i][0];j+=1) cout<<"(";
        cout<<i;
        for(int j=0;j<temp[i][1];j+=1) cout<<")";
    }    
    cout<<endl;
    return 0;
}