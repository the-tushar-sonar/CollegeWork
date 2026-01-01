#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    vector<int> at(n), bt(n), pr(n), ct(n), rt(n), wt(n), tat(n);
    for(int i=0;i<n;i++) cin >> at[i] >> bt[i] >> pr[i];

    vector<bool> done(n,false);
    int time=0, completed=0;

    while(completed<n){
        int idx=-1, best=INT_MAX;
        for(int i=0;i<n;i++)
            if(!done[i] && at[i]<=time && pr[i]<best)
                best=pr[i], idx=i;

        if(idx==-1){ time++; continue; }

        rt[idx]=time-at[idx];
        time+=bt[idx];
        ct[idx]=time;
        tat[idx]=ct[idx]-at[idx];
        wt[idx]=tat[idx]-bt[idx];
        done[idx]=true; completed++;
    }

    double aw=0, atg=0, ar=0, apr=0;
    for(int i=0;i<n;i++){
        double pen=(double)tat[i]/bt[i];
        aw+=wt[i]; atg+=tat[i]; ar+=rt[i]; apr+=pen;
        cout<<"P"<<i+1<<" "<<at[i]<<" "<<bt[i]<<" "<<ct[i]<<" "
            <<wt[i]<<" "<<tat[i]<<" "<<rt[i]<<" "<<pen<<"\n";
    }
    cout<<"Avg WT="<<aw/n<<" Avg TAT="<<atg/n<<" Avg RT="<<ar/n
        <<" Avg PR="<<apr/n<<" Throughput="<<(double)n/time;
}
