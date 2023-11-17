#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, x;
        cin >> n >> x;
        if (n == 1 || n == 2) {
            cout << 1 << endl;
        } else {
            n = n - 2;
            cout << (n-1) / x + 2 << endl;
        }
    }
}