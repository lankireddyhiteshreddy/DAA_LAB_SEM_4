#include<bits/stdc++.h>
using namespace std;
using namespace::chrono;

void generateRandomGraph(int n,vector<vector<int>> &adjMatrix) {
    srand(time(0)); 

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int weight = 1 + rand() %100;
            adjMatrix[i][j] = weight;
            adjMatrix[j][i] = weight;
        }
    }
    for (int i = 1; i < n; i++) {
        if (adjMatrix[i][0] == 0) {
            int weight = 1 + rand() % 100;
            adjMatrix[i][0] = weight;
            adjMatrix[0][i] = weight;
        }
    }
}


void primMST(int n, vector<vector<int>> &adjMatrix) {
    vector<int> parent(n, -1); 
    vector<int> key(n, INT_MAX); 
    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                key[v] = adjMatrix[u][v];
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
}

void generateLinearGraph(int n,vector<vector<int>> &adjMatrix) {
    srand(time(0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        int weight = 1 + rand() % 100; 
        adjMatrix[i][i + 1] = weight;
        adjMatrix[i + 1][i] = weight; 
    }
}

void generateCompleteGraph(int n, vector<vector<int>> &adjMatrix) {
    srand(time(0)); 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                adjMatrix[i][j] = 0; 
            } else if (j > i) { 
                int weight = 1 + rand() % 100;
                adjMatrix[i][j] = weight;
                adjMatrix[j][i] = weight; 
            }
        }
    }
}


int main() {
    vector<int> sizes = {5,10,15,30,50,100,200,500,750,1000,10000};
    for(auto n : sizes){
        double avg_time = 0;
        for(int i=0;i<10;i+=1){
            vector<vector<int>> g(n,vector<int>(n));
            generateRandomGraph(n,g);
            auto start = high_resolution_clock::now();
            primMST(n,g);
            auto end = high_resolution_clock::now();
            avg_time+= duration_cast<nanoseconds>(end-start).count();
        }
        avg_time = avg_time/10;
        double best_case_time = 0;
        vector<vector<int>> gmin(n,vector<int>(n));
        generateLinearGraph(n,gmin);
        auto start = high_resolution_clock::now();
        primMST(n,gmin);
        auto end = high_resolution_clock::now();
        best_case_time = duration_cast<nanoseconds>(end-start).count();
        vector<vector<int>> gmax(n,vector<int>(n));
        generateCompleteGraph(n,gmax);
        double worst_case_time = 0;
        start = high_resolution_clock::now();
        primMST(n,gmax);
        end = high_resolution_clock::now();
        worst_case_time = duration_cast<nanoseconds>(end-start).count();

        cout<<n<<","<<best_case_time<<","<<avg_time<<","<<worst_case_time<<endl;
    }
    return 0;
}
