#include<bits/stdc++.h>
using namespace std;

bool checkNegCycle(vector<vector<int>> &edges,vector<int> &d){
    for(int i=0;i<edges.size();i+=1){
        int v1 = edges[i][0];
        int v2 = edges[i][1];
        int wt = edges[i][2];
        if(wt!=0 && d[v1]!=1e9 && d[v2]>d[v1]+wt){
            return false;
        }
    }
    return true;
}

bool bellmanFord(int n,int src,vector<vector<int>> &g,vector<int> &d,vector<int> &p){
    vector<vector<int>> edges;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(g[i][j] != 0 && g[i][j] != 1e9){ 
                edges.push_back({i, j, g[i][j]});
            }
        }
    }
    
    d[src] = 0;
    for(int i=0;i<n-1;i+=1){
        for(int j=0;j<edges.size();j+=1){
            int v1 = edges[j][0];
            int v2 = edges[j][1];
            int wt = edges[j][2];
            if(wt!=0 && d[v1]!=1e9 && d[v2]>d[v1]+wt){
                d[v2] = d[v1] + wt;
                p[v2] = v1;
            }
        }
    }
    return checkNegCycle(edges,d);
}

void printPath(int node,vector<int>& p){
    if(node==-1) return;
    printPath(p[node],p);
    cout<<node<<" ";
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
    vector<int> dist(n,1e9);
    vector<int> parent(n,-1);
    bool val = bellmanFord(n,0,g,dist,parent);
    if(val==false){
        cout<<"Negative cycle detected"<<endl;
        return 0;
    }
    for(int i=0;i<n;i+=1){
        cout<<"Shortest path cost from 0 to "<<i<<" is : "<<dist[i]<<endl;
        cout<<"Shortest path from 0 to "<<i<<" is : ";
        printPath(i,parent);
        cout<<endl;
    }
}