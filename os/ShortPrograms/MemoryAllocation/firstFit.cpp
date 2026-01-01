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

    vector<int> alloc(n, -1);
    vector<bool> used(m,false);
    vector<int> frag(n,0);
    int total_frag = 0;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!used[j] && block[j] >= proc[i]){
                alloc[i]=j; used[j]=true;
                frag[i] = block[j] - proc[i];
                total_frag += frag[i];
                break;
            }
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
