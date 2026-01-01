#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, head, total=0;
    cin >> n;
    vector<int> req(n);
    for(int i=0;i<n;i++) cin >> req[i];
    cin >> head;

    cout << head;
    for(int r : req){
        total += abs(head - r);
        head = r;
        cout << " -> " << r;
    }
    cout << "\nTotal Seek = " << total;
    cout << "\nAverage Seek = " << (double)total/n;
}
