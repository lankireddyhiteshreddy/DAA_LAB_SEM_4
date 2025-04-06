#include<bits/stdc++.h>
using namespace std;

#define INF 1e9;

int tsp(int mask,int pos,vector<vector<int>> &d,vector<vector<int>> &dp,vector<vector<int>> &p){
    if(mask==((1<<d.size())-1)) return d[pos][0];

    if(dp[mask][pos]!=-1) return dp[mask][pos];

    int ans = INF;
    int minCity = -1;
    for(int city=0;city<d.size();city++){
        if(!(mask&(1<<city))){
            int val = d[pos][city] + tsp(mask|(1<<city),city,d,dp,p);
            if(val<ans){
                ans = val;
                minCity = city;
            }
        }
    }
    if(minCity!=-1){
        p[mask][pos] = minCity;
    }

    return dp[mask][pos] = ans;
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> dist(n,vector<int>(n));
    for(int i=0;i<n;i+=1){
        for(int j=0;j<n;j+=1){
            cin>>dist[i][j];
        }
    }

    vector<vector<int>> dp(1<<n,vector<int>(n,-1));
    vector<vector<int>> parent(1<<n,vector<int>(n,-1));
    int shortestDistance = tsp(1,0,dist,dp,parent);
    cout<<"Shortest path cost : "<<shortestDistance<<endl;
    cout<<"Shortest path : ";
    vector<int> shortestPath;
    shortestPath.push_back(0);
    int pos = 0;
    int mask = 1;
    while(true){
        int nextCity = parent[mask][pos];
        if(nextCity==-1) break;
        shortestPath.push_back(nextCity);
        mask|=(1<<nextCity);
        pos = nextCity;
    }
    shortestPath.push_back(0);
    for(int i=0;i<shortestPath.size();i+=1){
        cout<<shortestPath[i]<<" ";
    }
    cout<<endl;
}