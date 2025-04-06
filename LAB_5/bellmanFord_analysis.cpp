#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct Edge {
    int u, v, weight;
};

void generateRandomGraph(int n, vector<Edge> &edges) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int weight = 1 + rand() % 100;
            edges.push_back({i, j, weight});
            edges.push_back({j, i, weight});
        }
    }
}

void generateUniformGraph(int n, vector<Edge> &edges, int weight) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({i, j, weight});
            edges.push_back({j, i, weight});
        }
    }
}

void generateWorstCaseGraph(int n, vector<Edge> &edges) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int weight = 1 + rand() % 1000; 
                edges.push_back({i, j, weight});
            }
        }
    }
}

bool bellmanFord(int n, vector<Edge> &edges, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i < n; i++) {
        bool updated = false;
        for (auto &edge : edges) {
            if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
                updated = true;
            }
        }
        if (!updated) break;
    }

    for (auto &edge : edges) {
        if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
            return false;  
        }
    }
    return true;
}

int main() {
    srand(time(0));  
    vector<int> sizes = {5, 10, 15, 30, 50, 100, 200, 500, 750, 1000};
    
    for (auto n : sizes) {
        double avg_time = 0;
        
        for (int i = 0; i < 10; i++) {
            vector<Edge> edges;
            generateRandomGraph(n, edges);
            
            auto start = high_resolution_clock::now();
            bellmanFord(n, edges, 0);
            auto end = high_resolution_clock::now();
            
            avg_time += duration_cast<nanoseconds>(end - start).count(); 
        }
        avg_time /= 10;

        double best_case_time = 0;
        vector<Edge> gmin;
        generateUniformGraph(n, gmin, 1);  
        auto start = high_resolution_clock::now();
        bellmanFord(n, gmin, 0);
        auto end = high_resolution_clock::now();
        best_case_time = duration_cast<nanoseconds>(end - start).count();

        double worst_case_time = 0;
        vector<Edge> gmax;
        generateWorstCaseGraph(n, gmax);
        start = high_resolution_clock::now();
        bellmanFord(n, gmax, 0);
        end = high_resolution_clock::now();
        worst_case_time = duration_cast<nanoseconds>(end - start).count();

        cout << n << "," << best_case_time << "," << avg_time << "," << worst_case_time << endl;
    }
    return 0;
}
