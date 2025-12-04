#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void clook(vector<int> requests, int head)
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

    cout << "\nC-LOOK order: ";

    for (int r : right)
    {
        total += abs(current - r);
        current = r;
        cout << r << " ";
    }

    if (!left.empty())
    {
        total += abs(current - left[0]);
        current = left[0];
    }

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

    clook(requests, head);

    return 0;
}