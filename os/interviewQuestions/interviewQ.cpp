#include <iostream>
using namespace std;

int main()
{
    int a = 5, b = 7;
    // Method 1:
    // a = a + b - (b = a);

    // Method 2:
    // a = a + b, b = a - b, a = a - b;

    // Method 3:
    // a = a ^ b ^ (b = a);

    // Method 4:
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    cout << "a: " << a << "\nb: " << b << endl;

    return 0;
}