#include <bits/stdc++.h>
using namespace std;

struct Connector {
    int start, end, weight;
};

void displayGraph(const vector<Connector> &links) {
    cout << "\nGraph Connections:\n";
    for (auto &link : links) {
        cout << link.start << " -> " << link.end << " : " << link.weight << endl;
    }
}

void displayDistances(int totalNodes, const vector<int> &range) {
    cout << "\nUpdated Distances:\n";
    for (int idx = 0; idx < totalNodes; idx++) {
        cout << "Node " << idx << " : " << (range[idx] == INT_MAX ? "INF" : to_string(range[idx])) << endl;
    }
}

void trackPath(int source, const vector<int> &trace, int target, const vector<Connector> &links) {
    if (target == -1) {
        cout << "No valid path from " << source << " to " << target << endl;
        return;
    }

    vector<int> route;
    for (int x = target; x != -1; x = trace[x]) {
        route.push_back(x);
    }
    reverse(route.begin(), route.end());

    cout << "Path from " << source << " to " << target << ": ";
    for (int step : route) {
        cout << step << " ";
    }
    cout << "\nTotal Weight: ";

    int totalWeight = 0;
    for (size_t idx = 0; idx < route.size() - 1; ++idx) {
        for (auto &link : links) {
            if (link.start == route[idx] && link.end == route[idx + 1]) {
                totalWeight += link.weight;
                break;
            }
        }
    }
    cout << totalWeight << endl;
}

void optimizedBellmanFord(int totalNodes, vector<Connector> &links, int origin) {
    vector<int> range(totalNodes, INT_MAX);
    vector<int> trace(totalNodes, -1);
    range[origin] = 0;

    for (int i = 1; i <= totalNodes - 1; i++) {
        bool modified = false;
        for (auto &link : links) {
            if (range[link.start] != INT_MAX && range[link.start] + link.weight < range[link.end]) {
                range[link.end] = range[link.start] + link.weight;
                trace[link.end] = link.start;
                modified = true;
            }
        }
        if (!modified) break;
        displayDistances(totalNodes, range);
    }

    for (auto &link : links) {
        if (range[link.start] != INT_MAX && range[link.start] + link.weight < range[link.end]) {
            cout << "Negative cycle detected!\n";
            return;
        }
    }

    cout << "\nFinal Distances from Node " << origin << "\n";
    displayDistances(totalNodes, range);

    for (int idx = 0; idx < totalNodes; ++idx) {
        if (idx != origin) {
            trackPath(origin, trace, idx, links);
        }
    }
}

void buildRandomGraph(int totalNodes, vector<Connector> &links) {
    srand(time(0));
    for (int i = 0; i < totalNodes; i++) {
        for (int j = i + 1; j < totalNodes; j++) {
            int randomWeight = -20 + rand() % 41;
            links.push_back({i, j, randomWeight});
            links.push_back({j, i, randomWeight});
        }
    }
    displayGraph(links);
}

int main() {
    int totalNodes, userChoice, origin;
    cout << "Enter total nodes: ";
    cin >> totalNodes;

    vector<Connector> links;

    cout << "Choose method:\n";
    cout << "1. Manual Entry\n2. Auto-Generated Graph\n";
    cin >> userChoice;

    if (userChoice == 1) {
        int totalLinks;
        cout << "Enter total connections: ";
        cin >> totalLinks;
        cout << "Enter connections (start end weight):\n";
        for (int i = 0; i < totalLinks; i++) {
            int s, e, w;
            cin >> s >> e >> w;
            links.push_back({s, e, w});
        }
    } else if (userChoice == 2) {
        buildRandomGraph(totalNodes, links);
    } else {
        cout << "Invalid option selected!\n";
        return 0;
    }

    cout << "Enter starting node: ";
    cin >> origin;
    optimizedBellmanFord(totalNodes, links, origin);

    return 0;
}
