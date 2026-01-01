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

    int pos = lower_bound(req.begin(), req.end(), head) - req.begin();
    for(int i=pos;i<n;i++){
        total += abs(head-req[i]);
        head=req[i]; cout<<" -> "<<head;
    }
    for(int i=0;i<pos;i++){
        total += abs(head-req[i]);
        head=req[i]; cout<<" -> "<<head;
    }

    cout<<"\nTotal Seek = "<<total;
    cout<<"\nAverage Seek = "<<(double)total/n;
}
