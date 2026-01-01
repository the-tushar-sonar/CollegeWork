#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, tq; 
    cin >> n;
    vector<int> at(n), bt(n), rem(n), ct(n), rt(n, -1);
    for(int i=0;i<n;i++){ cin >> at[i] >> bt[i]; rem[i]=bt[i]; }
    cin >> tq;

    queue<int> q;
    vector<bool> inQ(n,false);
    int time=0, done=0;

    while(done<n){
        for(int i=0;i<n;i++)
            if(at[i]<=time && rem[i]>0 && !inQ[i])
                q.push(i), inQ[i]=true;

        if(q.empty()){ time++; continue; }

        int p=q.front(); q.pop();
        if(rt[p]==-1) rt[p]=time-at[p];

        int exec=min(tq, rem[p]);
        rem[p]-=exec; time+=exec;

        for(int i=0;i<n;i++)
            if(at[i]<=time && rem[i]>0 && !inQ[i])
                q.push(i), inQ[i]=true;

        if(rem[p]>0) q.push(p);
        else ct[p]=time, done++;
    }

    double aw=0, atg=0, ar=0, apr=0;
    for(int i=0;i<n;i++){
        int tat=ct[i]-at[i], wt=tat-bt[i];
        double pr=(double)tat/bt[i];
        aw+=wt; atg+=tat; ar+=rt[i]; apr+=pr;
        cout<<"P"<<i+1<<" "<<at[i]<<" "<<bt[i]<<" "<<ct[i]<<" "
            <<wt<<" "<<tat<<" "<<rt[i]<<" "<<pr<<"\n";
    }
    cout<<"Avg WT = "<<aw/n<<" Avg TAT = "<<atg/n<<" Avg RT = "<<ar/n
        <<" Avg PR = "<<apr/n<<" Throughput = "<<(double)n/time;
}
