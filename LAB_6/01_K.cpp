#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
 
int computeMaxValue(int capacity, vector<int> &wt, vector<int> &val, int itemCount, bool showSteps) {
    vector<vector<int>> table(itemCount + 1, vector<int>(capacity + 1, 0));
 
    for (int idx = 1; idx <= itemCount; idx++) {
        for (int cap = 0; cap <= capacity; cap++) {
            if (wt[idx - 1] <= cap)
                table[idx][cap] = max(val[idx - 1] + table[idx - 1][cap - wt[idx - 1]], table[idx - 1][cap]);
            else
                table[idx][cap] = table[idx - 1][cap];
        }
    }
 
    if (showSteps) {
        cout << "\nDP Table (Intermediate Steps):\n";
        for (int i = 0; i <= itemCount; i++) {
            for (int w = 0; w <= capacity; w++) {
                cout << setw(4) << table[i][w] << " ";
            }
            cout << endl;
        }
 
        cout << "\nItems Selected:\n";
        int cap = capacity;
        for (int idx = itemCount; idx > 0 && cap > 0; idx--) {
            if (table[idx][cap] != table[idx - 1][cap]) {
                cout << "Item " << idx << " (Weight: " << wt[idx - 1] << ", Value: " << val[idx - 1] << ")\n";
                cap -= wt[idx - 1];
            }
        }
    }
 
    return table[itemCount][capacity];
}
 
int main() {
    srand(time(0));
    int userChoice;
 
    cout << "Choose input method:\n";
    cout << "1. Manual item entry\n";
    cout << "2. Auto-generate random items (Test sizes: 100, 500, 1000, 5000, 10000)\n";
    cout << "Enter choice: ";
    cin >> userChoice;
 
    if (userChoice == 1) {
        int itemCount, maxCapacity;
        cout << "Enter number of items: ";
        cin >> itemCount;
        cout << "Enter maximum weight limit: ";
        cin >> maxCapacity;
 
        vector<int> wt(itemCount), val(itemCount);
        cout << "Enter weight and value for each item:\n";
        for (int i = 0; i < itemCount; i++) {
            cout << "Item " << i + 1 << " - Weight: ";
            cin >> wt[i];
            cout << "        Value: ";
            cin >> val[i];
        }
 
        bool showSteps = (itemCount <= 5); 
        auto start = high_resolution_clock::now();
        int result = computeMaxValue(maxCapacity, wt, val, itemCount, showSteps);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
 
        cout << "\nMaximum Value in 0/1 Knapsack: " << result;
        cout << "\nExecution Time: " << duration.count() << " ms\n";
 
    } else if (userChoice == 2) {
        vector<int> sampleSizes = {100, 500, 1000, 5000, 10000};
        int maxCapacityLimit = 5000;
 
        for (int itemCount : sampleSizes) {
            int maxCapacity = rand() % maxCapacityLimit + 1000;
 
            vector<int> wt(itemCount), val(itemCount);
            for (int i = 0; i < itemCount; i++) {
                wt[i] = rand() % 100 + 1;
                val[i] = rand() % 200 + 1;
            }
 
            cout << "\n====================================";
            cout << "\nTesting for n = " << itemCount << ", Max Capacity = " << maxCapacity;
            cout << "\n====================================";
 
            bool showSteps = (itemCount <= 5);
 
            auto start = high_resolution_clock::now();
            int result = computeMaxValue(maxCapacity, wt, val, itemCount, showSteps);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
 
            cout << "\nMaximum Value in 0/1 Knapsack: " << result;
            cout << "\nExecution Time: " << duration.count() << " ms\n";
        }
    } else {
        cout << "Invalid choice! Exiting...\n";
    }
 
    return 0;
}