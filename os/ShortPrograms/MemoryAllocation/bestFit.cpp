#include <bits/stdc++.h>
using namespace std;

int main(){
    int m; 
    if(!(cin>>m)) return 0;
    vector<int> block(m);
    for(int i=0;i<m;i++) cin>>block[i];
    int n; cin>>n;
    vector<int> proc(n);
    for(int i=0;i<n;i++) cin>>proc[i];

    vector<int> alloc(n,-1), frag(n,0);
    vector<bool> used(m,false);
    int total_frag=0;

    for(int i=0;i<n;i++){
        int best=-1;
        for(int j=0;j<m;j++){
            if(!used[j] && block[j]>=proc[i]){
                if(best==-1 || block[j] < block[best]) best=j;
            }
        }
        if(best!=-1){
            alloc[i]=best; used[best]=true;
            frag[i]=block[best]-proc[i];
            total_frag+=frag[i];
        }
    }

    for(int i=0;i<n;i++){
        cout<<"P"<<i+1<<": Size="<<proc[i]<<" -> ";
        if(alloc[i]==-1) cout<<"Not Allocated";
        else cout<<"Block "<<alloc[i]+1<<" (Frag="<<frag[i]<<")";
        cout<<"\n";
    }
    cout<<"Total Internal Fragmentation = "<<total_frag<<"\n";
    cout<<"Average Internal Fragmentation = "<<fixed<<setprecision(2)
        <<(double)total_frag/n<<"\n";
}
