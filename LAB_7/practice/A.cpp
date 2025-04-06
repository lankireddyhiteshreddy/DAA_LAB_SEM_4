#include<bits/stdc++.h>
using namespace std;

int MCM(int i,int j,vector<int> &dim,vector<vector<int>> &dp,vector<vector<int>> &s){
    if(i==j) return 0;
    if(dp[i][j]!=-1) return dp[i][j];

    int minMult = 1e9;
    for(int k=i;k<j;k+=1){
        int val = MCM(i,k,dim,dp,s) + MCM(k+1,j,dim,dp,s) + dim[i-1]*dim[k]*dim[j];
        if(minMult>val){
            minMult = val;
            s[i][j] = k;
        }
    }
    return dp[i][j] = minMult;
}

int main(){
    int n;
    cin>>n;
    vector<int> dim(n+1);
    
    for(int i=0;i<=n;i+=1){
        cin>>dim[i];
    }
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    vector<vector<int>> s(n+1,vector<int>(n+1));
    int optimulMultiplications = MCM(1,n,dim,dp,s);
    cout<<"Minimum multiplications = "<<optimulMultiplications<<endl;
}