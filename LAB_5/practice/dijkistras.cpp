#include<bits/stdc++.h>
using namespace std;

void dij(int src,vector<vector<int>> &g,vector<int> &dist,vector<int> &p){
    set<vector<int>> s;
    dist[src] = 0; 
    s.insert({0,src});
    while(!s.empty()){
        auto it = *(s.begin());
        int node = it[1];
        int dis = it[0];
        s.erase(it);

        for(int i=0;i<g.size();i+=1){
            if(g[node][i]>0 && dist[i]>dis + g[node][i]){
                dist[i] = dis+g[node][i];
                p[i] = node;
                s.insert({dis+g[node][i],i});
            }
        }

    }
}

void printPath(int node,vector<int> &p){
    if(node==-1) return;
    printPath(p[node],p);
    cout<<node<<" ";
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> g(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j+=1){
            cin>>g[i][j];
        }
    }
    vector<int> dist(n,1e9);
    vector<int> parent(n,-1);
    dij(0,g,dist,parent);
    for(int i=0;i<n;i+=1){
        cout<<"Shortest path cost from 0 to "<<i<<" is : "<<dist[i]<<endl;
        cout<<"Shortest path from 0 to "<<i<<" is : ";
        printPath(i,parent);
        cout<<endl;
    }
}