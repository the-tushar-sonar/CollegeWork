#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void SCAN(vector<int> requests, int head, int disk_size, string direction)
{
    vector<int> left, right;

    for (int r : requests)
    {
        if (r < head)
            left.push_back(r);
        else
            right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int total_seek = 0, current = head;

    cout << "\nSCAN Seek Sequence: ";

    if (direction == "right")
    {
        // Move to the right
        for (int r : right)
        {
            cout << r << " ";
            total_seek += abs(current - r);
            current = r;
        }

        // Go to disk end
        total_seek += abs(current - (disk_size - 1));
        current = disk_size - 1;

        // Move left
        for (int i = left.size() - 1; i >= 0; i--)
        {
            cout << left[i] << " ";
            total_seek += abs(current - left[i]);
            current = left[i];
        }
    }
    else
    { // direction = left
        // Move left
        for (int i = left.size() - 1; i >= 0; i--)
        {
            cout << left[i] << " ";
            total_seek += abs(current - left[i]);
            current = left[i];
        }

        // Go to disk start
        total_seek += abs(current - 0);
        current = 0;

        // Move right
        for (int r : right)
        {
            cout << r << " ";
            total_seek += abs(current - r);
            current = r;
        }
    }

    cout << "\nTotal Seek Time: " << total_seek << endl;
}

int main()
{
    vector<int> requests = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int disk_size = 200;

    SCAN(requests, head, disk_size, "right");

    return 0;
}
