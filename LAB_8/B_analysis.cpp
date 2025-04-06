#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
#define INF 1e9

int n;
vector<vector<int>> dist;

int primMST() {
    vector<int> minDist(n, INF), visited(n, 0);
    minDist[0] = 0;
    int totalWeight = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && (u == -1 || minDist[j] < minDist[u]))
                u = j;

        visited[u] = 1;
        totalWeight += minDist[u];

        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[u][v] < minDist[v])
                minDist[v] = dist[u][v];
        }
    }
    return totalWeight * 2; 
}

int main() {
    srand(time(0));
    vector<int> sizes = {10, 20, 30, 40, 50};

    for (auto size : sizes) {
        n = size;
        dist.clear();  
        dist.resize(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) dist[i][j] = 0;
                else dist[i][j] = rand() % 100 + 1;
            }
        }

        auto start = high_resolution_clock::now();
        int approxResult = primMST();
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>(end - start).count();

        cout << "n = " << n << ", Approximation Result: " << approxResult 
             << ", Time Taken: " << duration << " ns" << endl;
    }

    return 0;
}
