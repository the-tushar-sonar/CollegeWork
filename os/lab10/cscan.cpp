#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void cscan(vector<int> requests, int head, int disk_size)
{
    sort(requests.begin(), requests.end());

    vector<int> left, right;
    for (int r : requests)
    {
        if (r < head)
            left.push_back(r);
        else
            right.push_back(r);
    }

    int total = 0;
    int current = head;

    cout << "\nC-SCAN order: ";

    // Move right
    for (int r : right)
    {
        total += abs(current - r);
        current = r;
        cout << r << " ";
    }

    // Jump to end then to start
    if (!left.empty())
    {
        total += abs((disk_size - 1) - current);
        total += (disk_size - 1);
        current = 0;
    }

    // Move right again
    for (int r : left)
    {
        total += abs(current - r);
        current = r;
        cout << r << " ";
    }

    cout << "\nTotal Head Movement: " << total << endl;
}

int main()
{
    vector<int> requests = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int disk_size = 200;

    cscan(requests, head, disk_size);

    return 0;
}
