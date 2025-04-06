#include<bits/stdc++.h>
using namespace std;

int spanningTree(int n,vector<vector<int>> &g){
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq;
    vector<int> v(n,0);
    pq.push({0,0,-1});
    int sum = 0;
    cout<<"Edges added : "<<endl;
    while(pq.size()!=0){
        auto it = pq.top();
        pq.pop();
        int fromNode = it[2];
        int node = it[1];
        int wt = it[0];

        if(v[node]) continue;
        v[node] = 1;
        if(it[2]!=-1) cout<<fromNode<<" "<<node<<" "<<endl;
        sum+=wt;

        for(int i=0;i<n;i+=1){
            if(g[node][i]>0 && !v[i]){
                pq.push({g[node][i],i,node});
            }
        }
    }
    return sum;
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> g(n,vector<int>(n));
    for(int i=0;i<n;i+=1){
        for(int j=0;j<n;j+=1){
            cin>>g[i][j];
        }
    }
    int ans = spanningTree(n,g);
    cout<<endl;
    cout<<"Minimal spanning tree cost : "<<ans<<endl;
}