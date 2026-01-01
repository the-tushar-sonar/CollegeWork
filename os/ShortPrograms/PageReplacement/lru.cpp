#include <bits/stdc++.h>
using namespace std;

int main(){
    int frames = 3;
    vector<int> ref = {3,2,1,2,3,4,3,2,1,3,4,2};

    vector<int> fr(frames, -1);
    unordered_map<int,int> last;
    int faults = 0;

    for(int i=0;i<ref.size();i++){
        int page = ref[i];
        bool hit = false;

        for(int f : fr) if(f == page) hit = true;

        if(!hit){
            int idx = -1;
            for(int j=0;j<frames;j++)
                if(fr[j] == -1){ idx = j; break; }

            if(idx == -1){
                int lru = INT_MAX;
                for(int j=0;j<frames;j++){
                    if(last[fr[j]] < lru){
                        lru = last[fr[j]];
                        idx = j;
                    }
                }
            }
            fr[idx] = page;
            faults++;
        }

        last[page] = i;

        cout << "Ref " << page << " ->";
        for(int f : fr) cout << " " << f;
        cout << " : " << (hit ? "Hit" : "Fault") << "\n";
    }

    cout << "Total Page Faults = " << faults << "\n";
    cout << "Fault Rate = " << fixed << setprecision(2)
         << (faults * 100.0 / ref.size()) << "%\n";
}
