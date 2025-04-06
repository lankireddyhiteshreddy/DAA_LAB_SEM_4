#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i+=1){
        cin>>a[i];
    }
    for(int t=1;t<n;t+=1){
        int f = 0;
        for(int i=0;i<n-t;i+=1){
            if(a[i]>a[i+1]){
                swap(a[i],a[i+1]);
                f=1;
            }
        }
        if(f==0){
            break;
        }
    }
    for(int i=0;i<n;i+=1) cout<<a[i]<<" ";
    cout<<endl;
}