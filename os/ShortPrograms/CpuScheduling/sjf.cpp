#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    vector<int> at(n), bt(n), ct(n), tat(n), wt(n), rt(n);
    for(int i=0;i<n;i++) cin>>at[i]>>bt[i];

    vector<bool> done(n,false);
    int time=0, completed=0;

    while(completed<n){
        int idx=-1, mn=INT_MAX;
        for(int i=0;i<n;i++)
            if(!done[i] && at[i]<=time && bt[i]<mn)
                mn=bt[i], idx=i;

        if(idx==-1){ time++; continue; }

        rt[idx]=time-at[idx];
        time+=bt[idx];
        ct[idx]=time;
        tat[idx]=ct[idx]-at[idx];
        wt[idx]=tat[idx]-bt[idx];
        done[idx]=true;
        completed++;
    }

    double aw=0,atg=0,ar=0,apr=0;
    for(int i=0;i<n;i++){
        double pr=(double)tat[i]/bt[i];
        aw+=wt[i]; atg+=tat[i]; ar+=rt[i]; apr+=pr;
        cout<<"P"<<i+1<<" "<<at[i]<<" "<<bt[i]<<" "<<ct[i]<<" "
            <<wt[i]<<" "<<tat[i]<<" "<<rt[i]<<" "<<pr<<"\n";
    }
    cout<<"Avg WT="<<aw/n<<" Avg TAT="<<atg/n<<" Avg RT="<<ar/n
        <<" Avg PR="<<apr/n<<" Throughput="<<(double)n/(time-*min_element(at.begin(),at.end()));
}
