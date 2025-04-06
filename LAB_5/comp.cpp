#include <bits/stdc++.h>
#include <chrono>
using namespace std;
 
// *Dijkstra's Algorithm* (Using Min Heap / Priority Queue)
void dijkstra(vector<vector<int>>& graph, int n, int src) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});
 
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
 
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
            }
        }
    }
}
 
// *Bellman-Ford Algorithm*
void bellmanFord(vector<vector<int>>& graph, int n, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
     
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }
}
 
// Generate a random weighted graph with n vertices
vector<vector<int>> generateRandomGraph(int n) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int weight = rand() % 100 + 1;
            graph[i][j] = graph[j][i] = weight;
        }
    }
    return graph;
}
 
int main() {
    vector<int> arr;
    ofstream f("ShortestPath.csv");
    f << "N,Dijkstra,BellmanFord" << endl;
     
    for (int i = 1; i < 1000; i++) {
        arr.push_back(i);
    }
    arr.push_back(10000);
     
    for (int i = 0; i < arr.size(); i++) {
        int n = arr[i];
        vector<vector<int>> graph = generateRandomGraph(n);
        int src = 0; // Source node
 
        clock_t start, end;
         
        // Measure time for Dijkstra's Algorithm
        start = clock();
        dijkstra(graph, n, src);
        end = clock();
        double dijkstra_time = double(end - start) / CLOCKS_PER_SEC;
        cout << "\nDijkstra's Algorithm Time: " << dijkstra_time << " seconds\n";
         
        // Measure time for Bellman-Ford Algorithm
        start = clock();
        bellmanFord(graph, n, src);
        end = clock();
        double bellmanford_time = double(end - start) / CLOCKS_PER_SEC;
        cout << "\nBellman-Ford Algorithm Time: " << bellmanford_time << " seconds\n";
         
        f << n << ',' << dijkstra_time << "," << bellmanford_time << endl;
    }
    f.close();
    return 0;
}