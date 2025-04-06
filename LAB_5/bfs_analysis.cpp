#include <bits/stdc++.h>
using namespace std;
using namespace::chrono;

struct Edge {
    int u, v;
};

void generateRandomGraph(int n, vector<Edge> &edges) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int weight = 1 + rand() % 100;
            edges.push_back({i, j});
            edges.push_back({j, i});
        }
    }
}

void generateUniformGraph(int n, vector<Edge> &edges, int weight) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({i, j});
            edges.push_back({j, i});
        }
    }
}

void generateWorstCaseGraph(int n, vector<Edge> &edges) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                edges.push_back({i, j});
            }
        }
    }
}

void bfs(int source, vector<vector<int>> &adj, vector<bool> &visited) {
    queue<int> q;
    visited[source] = true;
    q.push(source);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 5000};
    vector<string> results;

    for (auto n : sizes) {
        double avg_time = 0;
        
        for (int i = 0; i < 10; i++) {
            vector<Edge> edges;
            generateRandomGraph(n, edges);
            
            vector<vector<int>> adj(n);
            for (auto &edge : edges) {
                adj[edge.u].push_back(edge.v);
            }
            
            vector<bool> visited(n, false);
            auto start = high_resolution_clock::now();
            bfs(0, adj, visited); 
            auto end = high_resolution_clock::now();
            
            avg_time += duration_cast<nanoseconds>(end - start).count();
        }
        avg_time /= 10;


        double best_case_time = 0;
        vector<Edge> gmin;
        generateUniformGraph(n, gmin, 1);
        vector<vector<int>> adj_min(n);
        for (auto &edge : gmin) {
            adj_min[edge.u].push_back(edge.v);
        }
        vector<bool> visited_min(n, false);
        auto start = high_resolution_clock::now();
        bfs(0, adj_min, visited_min); 
        auto end = high_resolution_clock::now();
        best_case_time = duration_cast<nanoseconds>(end - start).count();

        double worst_case_time = 0;
        vector<Edge> gmax;
        generateWorstCaseGraph(n, gmax);
        vector<vector<int>> adj_max(n);
        for (auto &edge : gmax) {
            adj_max[edge.u].push_back(edge.v);
        }
        vector<bool> visited_max(n, false);
        auto start2 = high_resolution_clock::now();
        bfs(0, adj_max, visited_max); 
        auto end2 = high_resolution_clock::now();
        worst_case_time = duration_cast<nanoseconds>(end2 - start2).count();
        cout<<n<<","<<best_case_time<<","<<avg_time<<","<<worst_case_time<<endl;
    }
    
    return 0;
}
