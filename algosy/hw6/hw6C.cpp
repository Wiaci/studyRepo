#include <iostream>

struct node {
    int val;
    node* next;
    node(int val): val(val) {};
};

class list {
    node* first, last;

    void push_back(int val) {
        node n(val);
        if (!first) {
            first = &n;
            last = &n;
            
        }
    }
};

int main() {
    int n, m; cin >> n >> m;
    list l;
    for (int i = 0; i < n; i++) {

    }
}