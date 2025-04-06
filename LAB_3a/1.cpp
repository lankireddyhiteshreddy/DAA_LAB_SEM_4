#include<bits/stdc++.h>
using namespace std;
int partition(vector<int>& arr, int low, int high) {
    int random_index = low + rand() % (high - low + 1);
    swap(arr[low], arr[random_index]); // Choosing a random pivot
    int pivot = arr[low];
    int i = low + 1;
    
    for (int j = low + 1; j <= high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[low], arr[i - 1]);  
    return i - 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high); 
    }
}