#include <bits/stdc++.h>
using namespace std;

void LRU(int pages[], int n, int capacity) {
    unordered_set<int> s;
    unordered_map<int, int> indexes;
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        if (s.find(pages[i]) == s.end()) {
            pageFaults++;

            if (s.size() == capacity) {
                int lru = INT_MAX, val;
                for (int page : s) {
                    if (indexes[page] < lru) {
                        lru = indexes[page];
                        val = page;
                    }
                }
                s.erase(val);
            }
            s.insert(pages[i]);
        }
        indexes[pages[i]] = i;
    }

    cout << "LRU Page Faults = " << pageFaults << endl;
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    LRU(pages, n, capacity);
    return 0;
}
