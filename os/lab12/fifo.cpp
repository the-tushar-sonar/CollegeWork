#include <bits/stdc++.h>
using namespace std;

void FIFO(int pages[], int n, int capacity) {
    unordered_set<int> s;
    queue<int> q;
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        // Page fault
        if (s.find(pages[i]) == s.end()) {
            pageFaults++;

            // If frames are full, remove oldest page
            if (s.size() == capacity) {
                int old = q.front();
                q.pop();
                s.erase(old);
            }

            s.insert(pages[i]);
            q.push(pages[i]);
        }
    }

    cout << "FIFO Page Faults = " << pageFaults << endl;
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    FIFO(pages, n, capacity);
    return 0;
}