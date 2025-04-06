#include<bits/stdc++.h>
using namespace std;

void heapify(vector<int> &a,int n,int i){
    int right = 2*i+2;
    int left = 2*i+1;
    int largestNode = i;
    
    if(left<n && a[left]>a[largestNode]){
        largestNode = left;
    }
    if(right<n && a[right]>a[largestNode]){
        largestNode = right;
    }
    if(largestNode!=i){
        swap(a[i],a[largestNode]);
        heapify(a,n,largestNode);
    }
}

void heapSort(vector<int> &a,int n){
    int start = (n>>1)-1;
    for(int i=start;i>=0;i--){
        heapify(a,n,i);
    }

    for(int i=n-1;i>0;i-=1){
        swap(a[0],a[i]);
        heapify(a,i,0);
    }
}



int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i+=1) cin>>a[i];
    heapSort(a,n);
    for(int i=0;i<n;i+=1) cout<<a[i]<<" ";
    cout<<endl;
}