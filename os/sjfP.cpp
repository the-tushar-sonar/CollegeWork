#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, at, bt, remaining;
    int ct = 0, tat = 0, wt = 0, rt = -1;
    float pr = 0.0;
    bool completed = false;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time & Burst Time for Process " << i << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].id = i;
        p[i].remaining = p[i].bt;
    }

    int completed = 0, current_time = 0;
    string gantt = "";
    int last_id = -1;

    while (completed < n) {
        int idx = -1;
        int min_rem = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= current_time) {
                if (p[i].remaining < min_rem) {
                    min_rem = p[i].remaining;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        if (p[idx].rt == -1)
            p[idx].rt = current_time - p[idx].at;

        if (last_id != idx) {
            gantt += " | P" + to_string(p[idx].id) + "(" + to_string(current_time);
            last_id = idx;
        }

        p[idx].remaining--;
        current_time++;

        if (p[idx].remaining == 0) {
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].pr = (float)p[idx].tat / p[idx].bt;
            p[idx].completed = true;
            completed++;
            gantt += "-" + to_string(current_time) + ")";
        }
    }

    float total_tat = 0, total_wt = 0, total_rt = 0, total_pr = 0;
    int total_time = 0;
    for (auto &x : p) {
        total_tat += x.tat;
        total_wt += x.wt;
        total_rt += x.rt;
        total_pr += x.pr;
        total_time = max(total_time, x.ct);
    }

    cout << "\nPROCESS\tAT\tBT\tCT\tTAT\tWT\tRT\tPenalty\n";
    for (auto &x : p) {
        cout << "P" << x.id << "\t" << x.at << "\t" << x.bt << "\t" << x.ct
             << "\t" << x.tat << "\t" << x.wt << "\t" << x.rt << "\t"
             << fixed << setprecision(2) << x.pr << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n;
    cout << "\nAverage Response Time: " << total_rt / n;
    cout << "\nAverage Penalty Ratio: " << total_pr / n;
    cout << "\nThroughput: " << (float)n / total_time << "\n";

    cout << "\nGantt Chart:\n" << gantt << " |\n";
}