#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void look(vector<int> requests, int head)
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

    cout << "\nLOOK order: ";

    for (int r : right)
    {
        total += abs(current - r);
        current = r;
        cout << r << " ";
    }

    reverse(left.begin(), left.end());
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

    look(requests, head);

    return 0;
}
