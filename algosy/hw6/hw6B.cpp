#include <iostream>

using namespace std;

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int n, m; cin >> n >> m;
        bool found = false;
        for (int j = 0; j < n; j++) {
            int a1, a2, a3, a4; cin >> a1 >> a2 >> a3 >> a4;
            if (a3 == a2) found = true;
        }
        if (m % 2 == 1) {
            cout << "NO" << endl;
            continue;
        }
        if (found) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

}