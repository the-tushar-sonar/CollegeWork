#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

void SSTF(vector<int> requests, int head)
{
    int total_seek = 0;
    vector<int> req = requests;
    vector<bool> visited(req.size(), false);
    int current = head;

    cout << "\nSSTF Seek Sequence: ";

    for (int i = 0; i < req.size(); i++)
    {
        int min_dist = INT_MAX, index = -1;

        for (int j = 0; j < req.size(); j++)
        {
            if (!visited[j] && abs(current - req[j]) < min_dist)
            {
                min_dist = abs(current - req[j]);
                index = j;
            }
        }

        visited[index] = true;
        total_seek += abs(current - req[index]);
        current = req[index];
        cout << current << " ";
    }

    cout << "\nTotal Seek Time: " << total_seek << endl;
}

int main()
{
    vector<int> requests = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int disk_size = 200;

    SSTF(requests, head);

    return 0;
}
