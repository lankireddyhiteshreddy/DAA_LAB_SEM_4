#include<bits/stdc++.h>
using namespace std;

int divide(int s,int e,vector<int> &a){
    int pivotElement = a[s];
    int j = e;
    for(int i=s+1;i<=e;i+=1){
        if(a[i]>pivotElement){
            swap(a[i],a[j]);
            j--;
        }
    }
    swap(a[s],a[j]);
    return j;
}

void quickSort(int s,int e,vector<int> &a){
    if(s>=e) return;
    int pivot = divide(s,e,a);
    quickSort(s,pivot-1,a);
    quickSort(pivot+1,e,a);
}

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i+=1) cin>>a[i];
    quickSort(0,n-1,a);
    for(int i=0;i<n;i+=1){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}