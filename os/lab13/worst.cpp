#include <bits/stdc++.h>
using namespace std;

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    cout << "\nWorst Fit Allocation\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << " -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated\n";
    }
}

int main()
{
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};

    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    int block[m];
    memcpy(block, blockSize, sizeof(blockSize));

    worstFit(block, m, processSize, n);
    return 0;
}