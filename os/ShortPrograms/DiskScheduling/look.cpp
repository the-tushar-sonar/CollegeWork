#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, head, total=0;
    cin >> n;
    vector<int> req(n);
    for(int i=0;i<n;i++) cin >> req[i];
    cin >> head;

    sort(req.begin(), req.end());
    cout << head;

    for(int i=lower_bound(req.begin(),req.end(),head)-req.begin()-1;i>=0;i--){
        total += abs(head-req[i]);
        head=req[i]; cout<<" -> "<<head;
    }
    for(int i=lower_bound(req.begin(),req.end(),head)-req.begin();i<n;i++){
        total += abs(head-req[i]);
        head=req[i]; cout<<" -> "<<head;
    }

    cout<<"\nTotal Seek = "<<total;
    cout<<"\nAverage Seek = "<<(double)total/n;
}
