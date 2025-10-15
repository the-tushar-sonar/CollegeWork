#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Define process structure
struct Process
{
    int id;
    int burst;
    int arrival;
    int completion;
    int waiting;
    int turnaround;
    int response;
    float penalty;
};

int main()
{
    int n;
    cout << "Enter the number of processes -- ";
    cin >> n;

    vector<Process> p(n);

    // Input arrival and burst times
    for (int i = 0; i < n; i++)
    {
        p[i].id = i;
        cout << "Enter Arrival Time & Burst Time for Process " << i << " -- ";
        cin >> p[i].arrival;
        cin >> p[i].burst;
    }

    // Sort processes by arrival time
    sort(p.begin(), p.end(), [](const Process &a, const Process &b)
         { return a.arrival < b.arrival; });

    // FCFS scheduling calculations
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].arrival)
            current_time = p[i].arrival; 
        p[i].waiting = current_time - p[i].arrival;
        p[i].response = p[i].waiting;
        p[i].completion = current_time + p[i].burst; 
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].penalty = (float)p[i].turnaround / p[i].burst;

        current_time += p[i].burst;
    }

    // Compute averages
    float total_wt = 0, total_tat = 0, total_rt = 0, total_pr = 0;
    for (auto &proc : p)
    {
        total_wt += proc.waiting;
        total_tat += proc.turnaround;
        total_rt += proc.response;
        total_pr += proc.penalty;
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    float avg_rt = total_rt / n;
    float avg_pr = total_pr / n;

    // Throughput = processes completed / total time
    float total_time = 0;
    for (auto &proc : p)
        total_time = max(total_time, (float)proc.completion);
    float throughput = n / total_time;

    // Display results
    cout << "\nPROCESS\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\tWAITING TIME\tTURNAROUND TIME\tRESPONSE TIME\tPENALTY RATIO\n";
    for (auto &proc : p)
    {
        cout << "P" << proc.id << "\t"
             << proc.arrival << "\t\t"
             << proc.burst << "\t\t"
             << proc.completion << "\t\t"
             << proc.turnaround << "\t\t"
             << proc.waiting << "\t\t"
             << proc.response << "\t\t"
             << fixed << setprecision(2) << proc.penalty << endl;
    }

    cout << "\nAverage Waiting Time-- " << fixed << setprecision(6) << avg_wt << endl;
    cout << "Average Turnaround Time -- " << avg_tat << endl;
    cout << "Average Response Time -- " << avg_rt << endl;
    cout << "Average Penalty Ratio -- " << avg_pr << endl;
    cout << "Throughput -- " << throughput << endl;

    return 0;
}
