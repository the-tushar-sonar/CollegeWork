#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    vector<int> at(n), bt(n), pr(n), rem(n), ct(n), rt(n,-1);
    for(int i=0;i<n;i++){ cin>>at[i]>>bt[i]>>pr[i]; rem[i]=bt[i]; }

    int time=0, done=0;
    while(done<n){
        int idx=-1, best=INT_MAX;
        for(int i=0;i<n;i++)
            if(at[i]<=time && rem[i]>0 && pr[i]<best)
                best=pr[i], idx=i;

        if(idx==-1){ time++; continue; }

        if(rt[idx]==-1) rt[idx]=time-at[idx];
        rem[idx]--; time++;

        if(rem[idx]==0)
            ct[idx]=time, done++;
    }

    double aw=0, atg=0, ar=0, apr=0;
    for(int i=0;i<n;i++){
        int tat=ct[i]-at[i], wt=tat-bt[i];
        double pen=(double)tat/bt[i];
        aw+=wt; atg+=tat; ar+=rt[i]; apr+=pen;
        cout<<"P"<<i+1<<" "<<at[i]<<" "<<bt[i]<<" "<<ct[i]<<" "
            <<wt<<" "<<tat<<" "<<rt[i]<<" "<<pen<<"\n";
    }
    cout<<"Avg WT="<<aw/n<<" Avg TAT="<<atg/n<<" Avg RT="<<ar/n
        <<" Avg PR="<<apr/n<<" Throughput="<<(double)n/time;
}
