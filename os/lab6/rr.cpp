#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion = 0;
    int turnaround = 0;
    int waiting = 0;
    int response = 0;
    float penalty = 0.0f;
    bool started = false;
};

int main() {
    int n, tq;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter Arrival Time & Burst Time for Process " << i << " -- ";
        cin >> p[i].arrival >> p[i].burst;
        p[i].id = i;
        p[i].remaining = p[i].burst;
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;
    vector<bool> in_queue(n, false);
    int current_time = 0, completed = 0;
    string gantt = "";

    // Enqueue any processes arriving at time 0
    for (int i = 0; i < n; ++i) {
        if (p[i].arrival == 0) {
            q.push(i);
            in_queue[i] = true;
        }
    }

    // If no process at time 0, jump to earliest arrival
    if (q.empty()) {
        int min_at = p[0].arrival;
        for (int i = 1; i < n; ++i)
            min_at = min(min_at, p[i].arrival);
        current_time = min_at;
        for (int i = 0; i < n; ++i) {
            if (p[i].arrival == current_time) {
                q.push(i);
                in_queue[i] = true;
            }
        }
    }

    while (completed < n) {
        if (q.empty()) {
            // CPU is idle, jump forward until next arrival
            current_time++;
            for (int k = 0; k < n; ++k) {
                if (!in_queue[k] && p[k].remaining > 0 && p[k].arrival <= current_time) {
                    q.push(k);
                    in_queue[k] = true;
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();

        // Record response time for the first execution
        if (!p[idx].started) {
            p[idx].response = current_time - p[idx].arrival;
            p[idx].started = true;
        }

        // Actual time process runs this round
        int exec_time = min(tq, p[idx].remaining);
        int start_time = current_time;
        current_time += exec_time;
        p[idx].remaining -= exec_time;

        // Record Gantt chart
        gantt += " | P" + to_string(p[idx].id) + "(" + to_string(start_time) + "-" + to_string(current_time) + ")";

        // Enqueue newly arrived processes during this execution
        for (int j = 0; j < n; ++j) {
            if (!in_queue[j] && p[j].remaining > 0 && p[j].arrival <= current_time) {
                q.push(j);
                in_queue[j] = true;
            }
        }

        // If process finished
        if (p[idx].remaining == 0) {
            p[idx].completion = current_time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            p[idx].penalty = (float)p[idx].turnaround / (float)p[idx].burst;
            ++completed;
        } else {
            q.push(idx); // Requeue if not finished
        }
    }

    // Compute averages
    float total_wt = 0, total_tat = 0, total_rt = 0, total_pr = 0;
    float total_time = 0;
    for (auto &proc : p) {
        total_wt += proc.waiting;
        total_tat += proc.turnaround;
        total_rt += proc.response;
        total_pr += proc.penalty;
        total_time = max(total_time, (float)proc.completion);
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    float avg_rt = total_rt / n;
    float avg_pr = total_pr / n;
    float throughput = (float)n / total_time;

    // Display results
    cout << "\nPROCESS\tAT\tBT\tCT\tTAT\tWT\tRT\tPENALTY\n";
    for (auto &proc : p) {
        cout << "P" << proc.id << "\t"
             << proc.arrival << "\t"
             << proc.burst << "\t"
             << proc.completion << "\t"
             << proc.turnaround << "\t"
             << proc.waiting << "\t"
             << proc.response << "\t"
             << fixed << setprecision(2) << proc.penalty << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avg_wt;
    cout << "\nAverage Turnaround Time: " << avg_tat;
    cout << "\nAverage Response Time: " << avg_rt;
    cout << "\nAverage Penalty Ratio: " << avg_pr;
    cout << "\nThroughput: " << throughput << "\n";

    cout << "\nGantt Chart:\n" << gantt << " |\n";

    return 0;
}
