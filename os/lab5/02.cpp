#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of processes -- ";
    cin >> n;

    int burst[n], waiting[n], turnaround[n], response[n];
    float penalty[n];

    // Input burst times
    for (int i = 0; i < n; i++) {
        cout << "Enter Burst Time for Process " << i << " -- ";
        cin >> burst[i];
    }

    // FCFS calculations
    waiting[0] = 0; // first process has no waiting time
    for (int i = 1; i < n; i++)
        waiting[i] = waiting[i - 1] + burst[i - 1];

    // Turnaround, response, and penalty ratio
    for (int i = 0; i < n; i++) {
        turnaround[i] = waiting[i] + burst[i];
        response[i] = waiting[i]; // same for FCFS
        penalty[i] = (float)turnaround[i] / burst[i];
    }

    // Compute averages
    float avg_wt = 0, avg_tat = 0, avg_rt = 0, avg_pr = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += waiting[i];
        avg_tat += turnaround[i];
        avg_rt += response[i];
        avg_pr += penalty[i];
    }

    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;
    avg_pr /= n;

    // Throughput = processes completed / total time
    float total_time = turnaround[n - 1];
    float throughput = (float)n / total_time;

    // Display output
    cout << "\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\tRESPONSE TIME\tPENALTY RATIO\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << "\t" << burst[i] << "\t\t"
             << waiting[i] << "\t\t"
             << turnaround[i] << "\t\t"
             << response[i] << "\t\t"
             << fixed << setprecision(2) << penalty[i] << endl;
    }

    cout << "Average Waiting Time-- " << fixed << setprecision(6) << avg_wt << endl;
    cout << "Average Turnaround Time -- " << avg_tat << endl;
    cout << "Average Response Time -- " << avg_rt << endl;
    cout << "Average Penalty Ratio -- " << avg_pr << endl;
    cout << "Throughput -- " << throughput << endl;

    return 0;
}
