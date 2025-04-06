#include<bits/stdc++.h>
using namespace std;

class DisjointSet{
public:
    vector<int> parent,size;
    DisjointSet(int n){
        parent.resize(n);
        size.resize(n,1);
        for(int i=0;i<n;i+=1){
            parent[i] = i;
        }
    }
    int UltP(int x){
        if(parent[x]==x) return x;
        else return parent[x] = UltP(parent[x]);
    }
    void combine(int x,int y){
        int UltPx = UltP(x);
        int UltPy = UltP(y);
        if(UltPx!=UltPy){
            if(size[UltPx]>size[UltPy]){
                parent[UltPy] = UltPx;
                size[UltPx]+=size[UltPy];
            }
            else{
                parent[UltPx] = UltPy;
                size[UltPy]+=size[UltPx];
            }
        }
    }
};

int kruskals(int n,vector<vector<int>> &g){
    vector<vector<int>> edges;
    for(int i=0;i<n;i+=1){
        for(int j=i+1;j<n;j+=1){
            if(g[i][j]>0){
                edges.push_back({g[i][j],i,j});
            }
        }
    }

    sort(edges.begin(),edges.end());

    DisjointSet DSU(n);
    int mstWt = 0;
    cout<<"Edges added : "<<endl;
    for(int i=0;i<edges.size();i+=1){
        int v1 = edges[i][1];
        int v2 = edges[i][2];
        int dist = edges[i][0];

        if(DSU.UltP(v1)!=DSU.UltP(v2)){
            cout<<v1<<" "<<v2<<endl;
            mstWt+=dist;
            DSU.combine(v1,v2);
        }
    }

    return mstWt;
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

    int cost = kruskals(n,g);

    cout<<"Cost : "<<cost<<endl;
}
