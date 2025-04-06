#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

int n;
vector<vector<int>> dist;
vector<vector<int>> dp;

int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) return dist[pos][0]; 

    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city))) {
            ans = min(ans, dist[pos][city] + tsp(mask | (1 << city), city));
        }
    }

    return dp[mask][pos] = ans;
}

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
    cout << "Enter number of cities: ";
    cin >> n;

    dist.resize(n, vector<int>(n));
    dp.resize(1 << n, vector<int>(n, -1));

    srand(time(0));
    cout << "\nDistance Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = rand() % 100 + 1;
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    int exactResult = tsp(1, 0);
    int approxResult = primMST();

    cout << "\nShortest Path Cost (Exact): " << exactResult << endl;
    cout << "Shortest Path Cost (Approximation): " << approxResult << endl;

    double approximationRatio = (double)approxResult / exactResult;
    cout << "Approximation Ratio: " << approximationRatio << endl;

    return 0;
}