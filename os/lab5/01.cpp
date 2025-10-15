#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int pid;        // process ID
    int arrival;    // arrival time
    int burst;      // burst time
};

int main() {
    queue<Process> readyQueue;

    // Example input
    readyQueue.push({1, 0, 5});
    readyQueue.push({2, 2, 3});
    readyQueue.push({3, 4, 1});

    int currentTime = 0;

    cout << "Process execution order (FCFS):\n";
    while (!readyQueue.empty()) {
        Process p = readyQueue.front();
        readyQueue.pop();

        if (currentTime < p.arrival)
            currentTime = p.arrival; // CPU waits for process to arrive

        cout << "Process " << p.pid
             << " starts at " << currentTime
             << " and finishes at " << currentTime + p.burst << endl;

        currentTime += p.burst;
    }

    return 0;
}
