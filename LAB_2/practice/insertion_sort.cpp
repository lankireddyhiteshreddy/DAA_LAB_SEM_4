#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i+=1) cin>>a[i];
    for(int i=1;i<n;i+=1){
        int key = a[i];
        int j = i-1;
        while(j>=0 && a[j]>key){
            a[j+1] = a[j];
            j--; 
        }
        a[j+1] = key;
    }
    for(int i=0;i<n;i+=1) cout<<a[i]<<" ";
    cout<<endl;
}