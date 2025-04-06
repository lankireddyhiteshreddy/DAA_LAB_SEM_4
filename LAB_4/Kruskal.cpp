#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

class DisjointSet {
public:
    vector<int> parent, rank;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

void printEdges(vector<Edge> &edges) {
    cout << "\nEdges in the Graph:\n";
    for (auto &edge : edges) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
}

void kruskalMST(int n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end());
    DisjointSet ds(n);
    vector<Edge> mst;
    
    cout << "\nEdges added to MST at each step:\n";
    for (auto &edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.unite(edge.u, edge.v);
            mst.push_back(edge);
            cout << "Step " << mst.size() << ": " << edge.u << " - " << edge.v << " (Weight: " << edge.weight << ")\n";
        }
    }
    
    cout << "\nFinal Minimum Spanning Tree (MST):\n";
    for (auto &edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
    
}
void generateRandomGraph(int n, vector<Edge> &edges) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int weight = 1 + rand() % 100;
            edges.push_back({i, j, weight});
        }
    }
    printEdges(edges);
}

int main() {
    int n, choice;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<Edge> edges;

    cout << "Choose an option:\n";
    cout << "1. Enter edges manually\n";
    cout << "2. Generate a random graph\n";
    cin >> choice;

    if (choice == 1) {
        int m;
        cout << "Enter number of edges: ";
        cin >> m;
        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
        }
    } else if (choice == 2) {
        generateRandomGraph(n, edges);
    } else {
        cout << "Invalid choice!\n";
        return 0;
    }

    kruskalMST(n, edges);
    return 0;
}
