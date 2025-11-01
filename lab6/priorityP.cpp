#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Process
{
    int id;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion = 0;
    int turnaround = 0;
    int waiting = 0;
    int response = -1; // -1 means not started yet
    float penalty = 0.0f;
    bool done = false;
};

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i)
    {
        cout << "Enter Arrival Time, Burst Time and Priority for Process " << i << " -- ";
        cin >> p[i].arrival >> p[i].burst >> p[i].priority;
        p[i].id = i;
        p[i].remaining = p[i].burst;
    }

    int current_time = 0, completed = 0;
    string gantt = "";

    while (completed < n)
    {
        // Find process with highest priority among arrived ones
        int idx = -1;
        int best_priority = 1e9; // Lower number = higher priority
        for (int i = 0; i < n; ++i)
        {
            if (!p[i].done && p[i].arrival <= current_time)
            {
                if (p[i].priority < best_priority ||
                    (p[i].priority == best_priority && p[i].arrival < p[idx].arrival))
                {
                    best_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            // CPU is idle, move forward
            current_time++;
            continue;
        }

        // Record response time at first CPU access
        if (p[idx].response == -1)
            p[idx].response = current_time - p[idx].arrival;

        int start_time = current_time;

        // Execute for one time unit
        p[idx].remaining--;
        current_time++;

        // Record Gantt chart entry
        gantt += " | P" + to_string(p[idx].id) + "(" + to_string(start_time) + "-" + to_string(current_time) + ")";

        // If finished
        if (p[idx].remaining == 0)
        {
            p[idx].completion = current_time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            p[idx].penalty = (float)p[idx].turnaround / (float)p[idx].burst;
            p[idx].done = true;
            completed++;
        }
    }

    // Compute averages
    float total_wt = 0, total_tat = 0, total_rt = 0, total_pr = 0;
    float total_time = 0;

    for (auto &proc : p)
    {
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

    // Display result table
    cout << "\nPROCESS\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\tPENALTY\n";
    for (auto &proc : p)
    {
        cout << "P" << proc.id << "\t"
             << proc.arrival << "\t"
             << proc.burst << "\t"
             << proc.priority << "\t"
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

    cout << "\nGantt Chart:\n"
         << gantt << " |\n";

    return 0;
}