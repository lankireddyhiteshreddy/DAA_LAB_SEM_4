#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
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

int main() {
    srand(time(0));
    vector<int> sizes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (auto curr_n : sizes) {
        n = curr_n;  
        dist.clear();
        dp.clear();

        dist.resize(n, vector<int>(n));
        dp.resize(1 << n, vector<int>(n, -1));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) dist[i][j] = 0;
                else dist[i][j] = rand() % 100 + 1; 
            }
        }

        auto start = high_resolution_clock::now();
        int result = tsp(1, 0);
        auto end = high_resolution_clock::now();

        auto time = duration_cast<nanoseconds>(end - start).count();

        cout << n << "," << time << endl;
    }

    return 0;
}
