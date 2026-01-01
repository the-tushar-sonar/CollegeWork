#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, head, total=0;
    cin >> n;
    vector<int> req(n);
    for(int i=0;i<n;i++) cin >> req[i];
    cin >> head;

    vector<bool> done(n,false);
    cout << head;

    for(int i=0;i<n;i++){
        int idx=-1, mn=INT_MAX;
        for(int j=0;j<n;j++)
            if(!done[j] && abs(head-req[j])<mn)
                mn=abs(head-req[j]), idx=j;

        total += abs(head - req[idx]);
        head = req[idx];
        done[idx]=true;
        cout << " -> " << head;
    }
    cout << "\nTotal Seek = " << total;
    cout << "\nAverage Seek = " << (double)total/n;
}
