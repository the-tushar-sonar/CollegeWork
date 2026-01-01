#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, head, disk=199, total=0;
    cin >> n;
    vector<int> req(n);
    for(int i=0;i<n;i++) cin >> req[i];
    cin >> head;

    req.push_back(0);
    req.push_back(disk);
    sort(req.begin(), req.end());

    int pos = find(req.begin(), req.end(), head) - req.begin();
    cout << head;

    for(int i=pos+1;i<req.size();i++){
        total += abs(head-req[i]);
        head=req[i]; cout<<" -> "<<head;
    }
    total += disk;
    head=0; cout<<" -> "<<head;

    for(int i=0;i<pos;i++){
        total += abs(head-req[i]);
        head=req[i]; cout<<" -> "<<head;
    }

    cout<<"\nTotal Seek = "<<total;
    cout<<"\nAverage Seek = "<<(double)total/n;
}
