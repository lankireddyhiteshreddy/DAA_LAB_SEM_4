#include <bits/stdc++.h>
using namespace std;

struct Link {
    int start, end;
};

void displayLinks(vector<Link> &connections) {
    cout << "\nConnections in the Network:\n";
    for (auto &link : connections) {
        cout << link.start << " - " << link.end << endl;
    }
}

void breadthFirstTraversal(int startNode, vector<vector<int>> &graphLinks, vector<bool> &visitedNodes, vector<int> &exploredPath) {
    queue<int> nodeQueue;
    visitedNodes[startNode] = true;
    nodeQueue.push(startNode);

    while (!nodeQueue.empty()) {
        int currentNode = nodeQueue.front();
        nodeQueue.pop();
        exploredPath.push_back(currentNode);
        cout << "Visited: " << currentNode << endl;

        for (int neighbor : graphLinks[currentNode]) {
            if (!visitedNodes[neighbor]) {
                visitedNodes[neighbor] = true;
                nodeQueue.push(neighbor);
            }
        }
    }
}

void displayTraversalPath(vector<int> &exploredPath) {
    cout << "\nTraversal Route: ";
    for (int node : exploredPath) {
        cout << node << " ";
    }
    cout << endl;
}

void autoGenerateGraph(int totalNodes, vector<Link> &connections) {
    srand(time(0));
    for (int i = 0; i < totalNodes; i++) {
        for (int j = i + 1; j < totalNodes; j++) {
            connections.push_back({i, j});
            connections.push_back({j, i}); 
        }
    }
    displayLinks(connections);
}

int main() {
    int totalNodes, userChoice, startingNode;
    cout << "Enter number of nodes in the network: ";
    cin >> totalNodes;

    vector<Link> connections;

    cout << "Choose an option:\n";
    cout << "1. Enter connections manually\n";
    cout << "2. Generate a random network\n";
    cin >> userChoice;

    if (userChoice == 1) {
        int totalConnections;
        cout << "Enter number of connections: ";
        cin >> totalConnections;
        cout << "Enter connections (start end):\n";
        for (int i = 0; i < totalConnections; i++) {
            int start, end;
            cin >> start >> end;
            connections.push_back({start, end});
        }
    } else if (userChoice == 2) {
        autoGenerateGraph(totalNodes, connections);
    } else {
        cout << "Invalid option selected!\n";
        return 0;
    }

    vector<vector<int>> graphLinks(totalNodes);
    for (auto &link : connections) {
        graphLinks[link.start].push_back(link.end);
    }

    cout << "Enter the starting node for traversal: ";
    cin >> startingNode;

    vector<bool> visitedNodes(totalNodes, false);
    vector<int> exploredPath;

    breadthFirstTraversal(startingNode, graphLinks, visitedNodes, exploredPath);

    displayTraversalPath(exploredPath);

    return 0;
}
