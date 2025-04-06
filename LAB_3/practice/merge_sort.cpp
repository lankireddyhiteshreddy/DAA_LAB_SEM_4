#include<bits/stdc++.h>
using namespace std;

void merge(vector<int> &a,vector<int> &a1,vector<int> &a2){
    int i = 0;
    int j = 0;
    int k = 0;
    while(i<a1.size() && j<a2.size()){
        if(a1[i]<a2[j]){
            a[k++] = a1[i++];
        }
        else{
            a[k++] = a2[j++];
        }
    }
    while(i<a1.size()){
        a[k++] = a1[i++];
    }
    while(j<a2.size()){
        a[k++] = a2[j++];
    }
}

void mergeSort(vector<int> &a,int n){
    if(n<=1) return;
    int mid = (n>>1);
    vector<int> a1(mid);
    vector<int> a2(n-mid);
    for(int i=0;i<mid;i+=1){
        a1[i] = a[i];
    }
    for(int i=mid;i<n;i+=1){
        a2[i-mid] = a[i]; 
    }
    mergeSort(a1,mid);
    mergeSort(a2,n-mid);
    merge(a,a1,a2);
}

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i+=1) cin>>a[i];
    mergeSort(a,n);
    for(int i=0;i<n;i+=1){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}