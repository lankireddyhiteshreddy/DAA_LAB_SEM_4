#include <bits/stdc++.h>
using namespace std;
 
struct Connector {
    int start, end, weight;
};
 
void displayConnectors(vector<Connector> &links) {
    cout << "\nGraph Connections:\n";
    for (auto &link : links) {
        cout << link.start << " - " << link.end << " : " << link.weight << endl;
    }
}
 
void showPath(int startNode, vector<int> &route, vector<vector<pair<int, int>>> &network, int endNode) {
    if (endNode == -1) {
        cout << "No route from " << startNode << " to " << endNode << endl;
        return;
    }
    vector<int> trail;
    for (int v = endNode; v != -1; v = route[v]) {
        trail.push_back(v);
    }
    reverse(trail.begin(), trail.end());
     
    cout << "Path from " << startNode << " to " << endNode << ": ";
    for (int i : trail) cout << i << " ";
 
    int totalCost = 0;
    for (int i = 0; i < trail.size() - 1; ++i) {
        for (auto &p : network[trail[i]]) {
            if (p.first == trail[i + 1]) {
                totalCost += p.second;
                break;
            }
        }
    }
    cout << "\nTotal Path Cost: " << totalCost << endl;
}
 
bool detectNegativeLoop(int size, vector<Connector>& links) {
    vector<int> travelDist(size, INT_MAX);
    travelDist[0] = 0;
 
    for (int i = 0; i < size - 1; i++) {
        for (auto &l : links) {
            if (travelDist[l.start] != INT_MAX && travelDist[l.start] + l.weight < travelDist[l.end]) {
                travelDist[l.end] = travelDist[l.start] + l.weight;
            }
        }
    }
 
    for (auto &l : links) {
        if (travelDist[l.start] != INT_MAX && travelDist[l.start] + l.weight < travelDist[l.end]) {
            cout << "Detected Negative Loop!" << endl;
            return true;
        }
    }
    return false;
}
 
void findShortestPath(int size, vector<vector<pair<int, int>>> &network, int start) {
    vector<int> travelDist(size, INT_MAX);
    vector<int> route(size, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
     
    travelDist[start] = 0;
    pq.push({0, start});
 
    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();
         
        if (dist > travelDist[node]) continue;
         
        for (auto &p : network[node]) {
            int neighbor = p.first;
            int cost = p.second;
            if (travelDist[node] + cost < travelDist[neighbor]) {
                travelDist[neighbor] = travelDist[node] + cost;
                route[neighbor] = node;
                pq.push({travelDist[neighbor], neighbor});
            }
        }
    }
 
    cout << "\nDistances from Node " << start << ":\n";
    for (int i = 0; i < size; i++) {
        cout << "Node " << i << " : " << (travelDist[i] == INT_MAX ? "INF" : to_string(travelDist[i])) << endl;
    }
 
    for (int i = 0; i < size; ++i) {
        if (i != start) showPath(start, route, network, i); 
    }
}
 
int main() {
    int size, option, startPoint;
    cout << "Enter number of nodes: ";
    cin >> size;
 
    vector<Connector> links;
    vector<vector<pair<int, int>>> network(size);
 
    cout << "1. Manual Input\n2. Random Graph Generation\nChoose: ";
    cin >> option;
 
    if (option == 1) {
        int edges;
        cout << "Enter number of connections: ";
        cin >> edges;
        cout << "Enter links (start end weight):\n";
        for (int i = 0; i < edges; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            links.push_back({a, b, w});
            network[a].push_back({b, w});
            network[b].push_back({a, w});
        }
    } else if (option == 2) {
        srand(time(0));
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                int w = 1 + rand() % 100;
                links.push_back({i, j, w});
                network[i].push_back({j, w});
                network[j].push_back({i, w});
            }
        }
        displayConnectors(links);
    } else {
        cout << "Invalid option!" << endl;
        return 0;
    }
 
    if (detectNegativeLoop(size, links)) return 0;  
 
    cout << "Enter starting node: ";
    cin >> startPoint;
    findShortestPath(size, network, startPoint);
 
    return 0;
}