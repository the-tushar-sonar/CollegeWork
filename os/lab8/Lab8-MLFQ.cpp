#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int at;
    int bt;
    int remaining;
    int ct = 0;
    int tat = 0;
    int wt = 0;
    int rt = -1; // response time (first run - arrival)
    float penalty = 0;
    bool started = false;
    bool finished = false;
    int level = 0; // 0 -> Q0, 1 -> Q1, 2 -> Q2
};

// find earliest arrival after `time` among not-finished processes
int next_arrival_time(const vector<Process> &p, int time)
{
    int nxt = INT_MAX;
    for (auto &pr : p)
        if (!pr.finished && pr.remaining > 0 && pr.at > time)
            nxt = min(nxt, pr.at);
    return nxt == INT_MAX ? -1 : nxt;
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cout << "Enter number of processes: ";
    if (!(cin >> n) || n <= 0)
        return 0;

    vector<Process> p(n);
    cout << "Enter processes (pid at bt) one per line:\n";
    for (int i = 0; i < n; ++i)
    {
        p[i].pid = i;
        cin >> p[i].at >> p[i].bt;
        p[i].remaining = p[i].bt;
        p[i].level = 0; // all start in Q0
    }

    int q0;
    cout << "Enter time quantum for Q0: ";
    cin >> q0;
    const int q1 = 8;

    queue<int> Q0; // indices for Q0 (FIFO)
    deque<int> Q1; // indices for Q1 (we need push_front)
    vector<bool> inQ0(n, false), inQ1(n, false), inQ2(n, false);

    int time = 0;
    int completed = 0;

    // Gantt chart logging
    vector<int> gantt_idx;
    vector<int> gantt_start;
    vector<int> gantt_end;

    // Enqueue arrivals at time 0
    for (int i = 0; i < n; ++i)
    {
        if (p[i].at <= time)
        {
            Q0.push(i);
            inQ0[i] = true;
        }
    }
    // If nothing at 0, advance to earliest arrival
    if (Q0.empty())
    {
        int nxt = next_arrival_time(p, -1);
        if (nxt != -1)
        {
            time = nxt;
            for (int i = 0; i < n; ++i)
                if (p[i].at <= time && !inQ0[i])
                {
                    Q0.push(i);
                    inQ0[i] = true;
                }
        }
    }

    // Main scheduling loop
    while (completed < n)
    {
        // Add newly arrived processes to Q0
        for (int i = 0; i < n; ++i)
        {
            if (!inQ0[i] && p[i].remaining > 0 && p[i].at <= time)
            {
                Q0.push(i);
                inQ0[i] = true;
            }
        }

        // -------- Q0: Round Robin with q0 (highest priority) ----------
        if (!Q0.empty())
        {
            int idx = Q0.front();
            Q0.pop();
            inQ0[idx] = false;
            if (time < p[idx].at)
                time = p[idx].at;
            if (!p[idx].started)
            {
                p[idx].rt = time - p[idx].at;
                p[idx].started = true;
            }

            int exec = min(q0, p[idx].remaining);
            int start = time;
            p[idx].remaining -= exec;
            time += exec;

            // record gantt
            gantt_idx.push_back(idx);
            gantt_start.push_back(start);
            gantt_end.push_back(time);

            // enqueue arrivals that came during execution into Q0
            for (int j = 0; j < n; ++j)
            {
                if (!inQ0[j] && p[j].remaining > 0 && p[j].at <= time)
                {
                    Q0.push(j);
                    inQ0[j] = true;
                }
            }

            if (p[idx].remaining == 0)
            {
                p[idx].ct = time;
                p[idx].finished = true;
                ++completed;
            }
            else
            {
                // demote to Q1
                p[idx].level = 1;
                if (!inQ1[idx])
                {
                    Q1.push_back(idx);
                    inQ1[idx] = true;
                }
            }
            continue;
        }

        // -------- Q1: Round Robin with q1=8 (middle priority) ----------
        if (!Q1.empty())
        {
            int idx = Q1.front();
            Q1.pop_front();
            inQ1[idx] = false;
            if (time < p[idx].at)
                time = p[idx].at;
            if (!p[idx].started)
            {
                p[idx].rt = time - p[idx].at;
                p[idx].started = true;
            }

            int exec_allowed = min(q1, p[idx].remaining);
            int executed = 0;
            int start = time;
            bool preempted_by_Q0 = false;

            // execute unit-by-unit to allow immediate Q0 arrivals to preempt
            for (int t = 0; t < exec_allowed; ++t)
            {
                // execute 1 unit
                p[idx].remaining -= 1;
                time += 1;
                executed += 1;

                // enqueue arrivals into Q0 at this time instant
                for (int j = 0; j < n; ++j)
                {
                    if (!inQ0[j] && p[j].remaining > 0 && p[j].at <= time)
                    {
                        Q0.push(j);
                        inQ0[j] = true;
                    }
                }

                // if Q0 now has items, preempt Q1 immediately (after this unit)
                if (!Q0.empty() && t != exec_allowed - 1)
                {
                    preempted_by_Q0 = true;
                    break;
                }

                if (p[idx].remaining == 0)
                    break;
            }

            // // record gantt
            // gantt_idx.push_back(idx);
            // gantt_start.push_back(start);
            // gantt_end.push_back(time);

            // if (p[idx].remaining == 0)
            // {
            //     p[idx].ct = time;
            //     p[idx].finished = true;
            //     ++completed;
            // }
            // else
            // {
            //     if (preempted_by_Q0)
            //     {
            //         // requeue to front of Q1 so it resumes soon after Q0 tasks finish
            //         Q1.push_front(idx);
            //         inQ1[idx] = true;
            //     }
            //     else
            //     {
            //         // quantum exhausted -> demote to Q2
            //         p[idx].level = 2;
            //         inQ2[idx] = true;
            //     }
            // }
            // continue;
        }

        // -------- Q2: SRTF (lowest priority) ----------
        int chosen = -1;
        int min_rem = INT_MAX;
        for (int i = 0; i < n; ++i)
        {
            if (p[i].remaining > 0 && inQ2[i] && p[i].at <= time)
            {
                if (p[i].remaining < min_rem)
                {
                    min_rem = p[i].remaining;
                    chosen = i;
                }
            }
        }

        if (chosen == -1)
        {
            // advance time to next arrival (if any) or break
            int nxt = next_arrival_time(p, time);
            if (nxt == -1)
                break;
            // move time forward to next arrival (but at least +1 to avoid infinite loop)
            time = max(time + 1, nxt);
            // add newly arrived to Q0
            for (int j = 0; j < n; ++j)
            {
                if (!inQ0[j] && p[j].remaining > 0 && p[j].at <= time)
                {
                    Q0.push(j);
                    inQ0[j] = true;
                }
            }
            continue;
        }

        // execute chosen for 1 unit (SRTF unit-by-unit)
        int idx = chosen;
        if (time < p[idx].at)
            time = p[idx].at;
        if (!p[idx].started)
        {
            p[idx].rt = time - p[idx].at;
            p[idx].started = true;
        }
        int start = time;
        p[idx].remaining -= 1;
        time += 1;
        // log gantt
        gantt_idx.push_back(idx);
        gantt_start.push_back(start);
        gantt_end.push_back(time);

        // enqueue any arrivals to Q0 that occurred at this time
        for (int j = 0; j < n; ++j)
        {
            if (!inQ0[j] && p[j].remaining > 0 && p[j].at <= time)
            {
                Q0.push(j);
                inQ0[j] = true;
            }
        }

        if (p[idx].remaining == 0)
        {
            p[idx].ct = time;
            p[idx].finished = true;
            ++completed;
            inQ2[idx] = false;
        }
        else
        {
            inQ2[idx] = true; // remains eligible in Q2
        }
    } // end main while

    // compute metrics
    double total_tat = 0.0, total_wt = 0.0;
    for (int i = 0; i < n; ++i)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].penalty = (float)p[i].tat / (float)p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    // print table
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\tPenalty\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << i << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\t"
             << (p[i].rt >= 0 ? p[i].rt : 0) << "\t" << fixed << setprecision(2) << p[i].penalty << "\n";
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time = " << (total_tat / n) << "\n";
    cout << "Average Waiting Time    = " << (total_wt / n) << "\n";

    // // print compact Gantt chart (merge consecutive same pid segments)
    // cout << "\nGantt Chart:\n";
    // if (!gantt_idx.empty())
    // {
    //     vector<string> m_pid;
    //     vector<int> m_s;
    //     vector<int> m_e;
    //     m_pid.push_back(p[gantt_idx[0]].pid);
    //     m_s.push_back(gantt_start[0]);
    //     m_e.push_back(gantt_end[0]);
    //     for (size_t k = 1; k < gantt_idx.size(); ++k)
    //     {
    //         string cur = p[gantt_idx[k]].pid;
    //         if (cur == m_pid.back() && gantt_start[k] == m_e.back())
    //         {
    //             m_e.back() = gantt_end[k];
    //         }
    //         else
    //         {
    //             m_pid.push_back(cur);
    //             m_s.push_back(gantt_start[k]);
    //             m_e.push_back(gantt_end[k]);
    //         }
    //     }
    //     for (size_t k = 0; k < m_pid.size(); ++k)
    //     {
    //         cout << "| " << m_pid[k] << "(" << m_s[k] << "-" << m_e[k] << ") ";
    //     }
    //     cout << "|\n";
    // }
    // else
    // {
    //     cout << "(no execution)\n";
    // }

    return 0;
}
