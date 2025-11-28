#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void FCFS(vector<int> requests, int head)
{
    int total_seek = 0;
    int current = head;

    cout << "\nFCFS Seek Sequence: ";
    for (int req : requests)
    {
        cout << req << " ";
        total_seek += abs(current - req);
        current = req;
    }

    cout << "\nTotal Seek Time: " << total_seek << endl;
}

int main()
{
    vector<int> requests = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;

    FCFS(requests, head);
    return 0;
}