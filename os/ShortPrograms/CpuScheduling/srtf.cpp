#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    vector<int> at(n), bt(n), rt(n,-1), rem(n), ct(n);
    for(int i=0;i<n;i++){ cin>>at[i]>>bt[i]; rem[i]=bt[i]; }

    int time=0, done=0;
    while(done<n){
        int idx=-1, mn=INT_MAX;
        for(int i=0;i<n;i++)
            if(at[i]<=time && rem[i]>0 && rem[i]<mn)
                mn=rem[i], idx=i;

        if(idx==-1){ time++; continue; }

        if(rt[idx]==-1) rt[idx]=time-at[idx];
        rem[idx]--; time++;

        if(rem[idx]==0){
            ct[idx]=time;
            done++;
        }
    }

    double aw=0,atg=0,ar=0,apr=0;
    for(int i=0;i<n;i++){
        int tat=ct[i]-at[i];
        int wt=tat-bt[i];
        double pr=(double)tat/bt[i];
        aw+=wt; atg+=tat; ar+=rt[i]; apr+=pr;
        cout<<"P"<<i+1<<" "<<at[i]<<" "<<bt[i]<<" "<<ct[i]<<" "
            <<wt<<" "<<tat<<" "<<rt[i]<<" "<<pr<<"\n";
    }
    cout<<"Avg WT = "<<aw/n<<" Avg TAT = "<<atg/n<<" Avg RT = "<<ar/n
        <<" Avg PR = "<<apr/n<<" Throughput = "<<(double)n/(time-*min_element(at.begin(),at.end()));
}