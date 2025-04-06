#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i+=1){
        cin>>a[i];
    }

    for(int i=0;i<n-1;i+=1){
        int key = a[i];
        int mini = -1;
        int mine = INT_MAX;
        for(int j=i+1;j<n;j+=1){
            if(mine>a[j]){
                mine = a[j];
                mini = j;
            }
        }
        if(a[i]>mine){
            swap(a[i],a[mini]);
        }
    }
    for(int i=0;i<n;i+=1) cout<<a[i]<<" ";
    cout<<endl;
}