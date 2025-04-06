#include <bits/stdc++.h>
using namespace std;
using namespace::chrono;

void generateSparseRandomGraph(int n, vector<vector<pair<int, int>>> &adj) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2 == 0) {  
                int weight = 1 + rand() % 100;
                adj[i].push_back(make_pair(j, weight));
                adj[j].push_back(make_pair(i, weight));
            }
        }
    }
}

void generateUniformGraph(int n, vector<vector<pair<int, int>>> &adj, int weight) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            adj[i].push_back(make_pair(j, weight));
            adj[j].push_back(make_pair(i, weight));
        }
    }
}

void generateWorstCaseGraph(int n, vector<vector<pair<int, int>>> &adj) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int weight = 1 + rand() % 1000;
                adj[i].push_back(make_pair(j, weight));
            }
        }
    }
}

void dijkstra(int n, vector<vector<pair<int, int>>> &adj, int src) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    vector<int> sizes = {5, 10, 15, 30, 50, 100, 200, 500, 750, 1000, 10000};
    for (auto n : sizes) {
        double avg_time = 0;
        for (int i = 0; i < 10; i++) {
            vector<vector<pair<int, int>>> g(n);
            generateSparseRandomGraph(n, g);
            auto start = high_resolution_clock::now();
            dijkstra(n, g, 0);
            auto end = high_resolution_clock::now();
            avg_time += duration_cast<nanoseconds>(end - start).count();
        }
        avg_time /= 10;

        double best_case_time = 0;
        vector<vector<pair<int, int>>> gmin(n);
        generateUniformGraph(n, gmin, 1); 
        auto start = high_resolution_clock::now();
        dijkstra(n, gmin, 0);
        auto end = high_resolution_clock::now();
        best_case_time = duration_cast<nanoseconds>(end - start).count();

        double worst_case_time = 0;
        vector<vector<pair<int, int>>> gmax(n);
        generateWorstCaseGraph(n, gmax);  
        start = high_resolution_clock::now();
        dijkstra(n, gmax, 0);
        end = high_resolution_clock::now();
        worst_case_time = duration_cast<nanoseconds>(end - start).count();

        cout << n << "," << best_case_time << "," << avg_time << "," << worst_case_time << endl;
    }
    return 0;
}
