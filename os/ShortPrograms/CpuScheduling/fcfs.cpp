#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter arrival time and burst time for each process:\n";
    vector<int> at(n), bt(n), pid(n);
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cin >> at[i] >> bt[i];
    }

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b)
         { return at[a] < at[b]; });

    vector<int> ct(n), tat(n), wt(n), rt(n);
    int time = 0;
    for (int k : idx)
    {
        time = max(time, at[k]);
        rt[k] = time - at[k];
        time += bt[k];
        ct[k] = time;
        tat[k] = ct[k] - at[k];
        wt[k] = tat[k] - bt[k];
    }

    double aw = 0, atg = 0, ar = 0, apr = 0;
    cout << "PID\tAT\tBT\tCT\tWT\tTAT\tRT\tPR\n";
    for (int i = 0; i < n; i++)
    {
        double pr = (double)tat[i] / bt[i];
        aw += wt[i];
        atg += tat[i];
        ar += rt[i];
        apr += pr;
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t"
             << wt[i] << "\t" << tat[i] << "\t" << rt[i] << "\t" << pr << "\n";
    }
    cout << "\nAvg WT = " << aw / n << "\nAvg TAT = " << atg / n << "\nAvg RT = " << ar / n
         << "\nAvg PR = " << apr / n << "\nThroughput = " << (double)n / (ct[idx.back()] - at[idx[0]]) << endl;
}