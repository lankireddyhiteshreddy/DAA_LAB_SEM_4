#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

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

void kruskalMST(int n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end());
    DisjointSet ds(n);
    vector<Edge> mst;
    for (auto &edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.unite(edge.u, edge.v);
            mst.push_back(edge);
        }
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
}

void generateLinearGraph(int n, vector<Edge> &edges) {
    for (int i = 0; i < n - 1; i++) {
        int weight = 1 + rand() % 100;
        edges.push_back({i, i + 1, weight});
    }
}

void generateCompleteGraph(int n, vector<Edge> &edges) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int weight = 1 + rand() % 100;
            edges.push_back({i, j, weight});
        }
    }
}

int main() {
    vector<int> sizes = {5, 10, 15, 30, 50, 100, 200, 500, 750, 1000, 5000};
    for (auto n : sizes) {
        double avg_time = 0;
        for (int i = 0; i < 10; i++) {
            vector<Edge> edges;
            generateRandomGraph(n, edges);
            auto start = high_resolution_clock::now();
            kruskalMST(n, edges);
            auto end = high_resolution_clock::now();
            avg_time += duration_cast<nanoseconds>(end - start).count();
        }
        avg_time /= 10;
        
        vector<Edge> best_edges;
        generateLinearGraph(n, best_edges);
        auto start = high_resolution_clock::now();
        kruskalMST(n, best_edges);
        auto end = high_resolution_clock::now();
        double best_case_time = duration_cast<nanoseconds>(end - start).count();
        
        vector<Edge> worst_edges;
        generateCompleteGraph(n, worst_edges);
        start = high_resolution_clock::now();
        kruskalMST(n, worst_edges);
        end = high_resolution_clock::now();
        double worst_case_time = duration_cast<nanoseconds>(end - start).count();
        
        cout << n << "," << best_case_time << "," << avg_time << "," << worst_case_time << endl;
    }
    return 0;
}
