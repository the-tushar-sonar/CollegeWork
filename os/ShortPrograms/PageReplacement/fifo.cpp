#include <bits/stdc++.h>
using namespace std;

int main(){
    int frames = 3;
    vector<int> ref = {3,2,1,2,3,4,3,2,1,3,4,2};

    vector<int> fr(frames, -1);
    int ptr = 0, faults = 0;

    for(int page : ref){
        bool hit = false;
        for(int f : fr) if(f == page) hit = true;

        if(!hit){
            fr[ptr] = page;
            ptr = (ptr + 1) % frames;
            faults++;
        }

        cout << "Ref " << page << " ->";
        for(int f : fr) cout << " " << f;
        cout << " : " << (hit ? "Hit" : "Fault") << "\n";
    }

    cout << "Total Page Faults = " << faults << "\n";
    cout << "Fault Rate = " << fixed << setprecision(2)
         << (faults * 100.0 / ref.size()) << "%\n";
}
