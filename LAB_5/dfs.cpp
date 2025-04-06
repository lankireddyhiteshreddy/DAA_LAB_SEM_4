#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
 
struct Link {
    int start, stop;
};
 
void showLinks(vector<Link> &links) {
    cout << "\nGraph Edges:\n";
    for (auto &link : links) {
        cout << link.start << " -> " << link.stop << endl;
    }
}
 
void depthFirstSearch(int point, vector<vector<int>> &connections, vector<bool> &seen, vector<int> &track) {
    seen[point] = true;
    track.push_back(point);
    cout << "Visited Node: " << point << endl;
 
    for (int link : connections[point]) {
        if (!seen[link]) {
            depthFirstSearch(link, connections, seen, track);
        }
    }
}
 
void showTraversalPath(vector<int> &track) {
    cout << "\nDFS Traversal Path: ";
    for (int point : track) {
        cout << point << " ";
    }
    cout << endl;
}
 
void autoGenerateGraph(int totalPoints, vector<Link> &links) {
    srand(time(0));
    for (int i = 0; i < totalPoints; i++) {
        for (int j = i + 1; j < totalPoints; j++) {
            links.push_back({i, j});
            links.push_back({j, i});
        }
    }
    showLinks(links);
}
 
int main() {
    int nodesCount, option, beginPoint;
    cout << "Enter total vertices: ";
    cin >> nodesCount;
 
    vector<Link> links;
 
    cout << "Choose an option:\n";
    cout << "1. Manual Input\n";
    cout << "2. Auto-Generate Graph\n";
    cin >> option;
 
    if (option == 1) {
        int totalLinks;
        cout << "Enter number of edges: ";
        cin >> totalLinks;
        cout << "Enter edges (start stop):\n";
        for (int i = 0; i < totalLinks; i++) {
            int start, stop;
            cin >> start >> stop;
            links.push_back({start, stop});
        }
    } else if (option == 2) {
        autoGenerateGraph(nodesCount, links);
    } else {
        cout << "Invalid option selected!\n";
        return 0;
    }
 
    vector<vector<int>> connections(nodesCount);
    for (auto &link : links) {
        connections[link.start].push_back(link.stop);
    }
 
    cout << "Enter starting vertex for DFS: ";
    cin >> beginPoint;
 
    vector<bool> seen(nodesCount, false);
    vector<int> track;
 
    depthFirstSearch(beginPoint, connections, seen, track);
 
    showTraversalPath(track);
 
    return 0;
}