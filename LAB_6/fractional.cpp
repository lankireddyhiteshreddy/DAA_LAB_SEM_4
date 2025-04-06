#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct Product {
    int mass, worth;
    double worthPerMass;
};

bool sortByRatio(Product a, Product b) {
    return a.worthPerMass > b.worthPerMass;
}


double optimalKnapsack(int capacity, vector<Product> &items, int totalItems, bool showSteps) {
    sort(items.begin(), items.end(), sortByRatio);

    double maxWorth = 0.0;
    int remainingCapacity = capacity;

    for (int i = 0; i < totalItems && remainingCapacity > 0; i++) {
        if (items[i].mass <= remainingCapacity) {
            maxWorth += items[i].worth;
            remainingCapacity -= items[i].mass;
        } else {
            maxWorth += items[i].worthPerMass * remainingCapacity;
            remainingCapacity = 0;
        }
    }

    if (showSteps) {
        cout << "\nSorted Items (by Value/Weight ratio):\n";
        for (auto item : items)
            cout << "Mass: " << item.mass << ", Worth: " << item.worth 
                 << ", Ratio: " << fixed << setprecision(2) << item.worthPerMass << endl;
    }
    return maxWorth;
}

int main() {
    srand(time(0));
    int option;

    cout << "Choose input method:\n";
    cout << "1. Enter items manually\n";
    cout << "2. Generate random items (Test cases: 100, 500, 1000, 5000, 10000)\n";
    cout << "Enter option: ";
    cin >> option;

    if (option == 1) {
        int totalItems, capacity;
        cout << "Enter number of items: ";
        cin >> totalItems;
        cout << "Enter capacity limit: ";
        cin >> capacity;

        vector<Product> items(totalItems);
        cout << "Enter mass and worth for each item:\n";
        for (int i = 0; i < totalItems; i++) {
            cout << "Item " << i + 1 << " - Mass: ";
            cin >> items[i].mass;
            cout << "        Worth: ";
            cin >> items[i].worth;
            items[i].worthPerMass = (double)items[i].worth / items[i].mass;
        }

        bool showSteps = (totalItems <= 5);
        auto start = high_resolution_clock::now();
        double maxWorth = optimalKnapsack(capacity, items, totalItems, showSteps);
        auto end = high_resolution_clock::now();
        auto execTime = duration_cast<milliseconds>(end - start);

        cout << "\nMaximum Worth in Fractional Knapsack: " << fixed << setprecision(2) << maxWorth;
        cout << "\nExecution Time: " << execTime.count() << " ms\n";

    } else if (option == 2) {
        vector<int> testSizes = {100, 500, 1000, 5000, 10000};
        int maxCapacity = 5000;

        for (int totalItems : testSizes) {
            int capacity = rand() % maxCapacity + 1000;

            vector<Product> items(totalItems);
            for (int i = 0; i < totalItems; i++) {
                items[i].mass = rand() % 100 + 1;
                items[i].worth = rand() % 200 + 1;
                items[i].worthPerMass = (double)items[i].worth / items[i].mass;
            }

            cout << "\n====================================";
            cout << "\nTesting for Items = " << totalItems << ", Capacity = " << capacity;
            cout << "\n====================================";

            bool showSteps = (totalItems <= 5);
            auto start = high_resolution_clock::now();
            double maxWorth = optimalKnapsack(capacity, items, totalItems, showSteps);
            auto end = high_resolution_clock::now();
            auto execTime = duration_cast<milliseconds>(end - start);

            cout << "\nMaximum Worth in Fractional Knapsack: " << fixed << setprecision(2) << maxWorth;
            cout << "\nExecution Time: " << execTime.count() << " ms\n";
        }
    } else {
        cout << "Invalid choice! Exiting...\n";
    }
    return 0;
}
