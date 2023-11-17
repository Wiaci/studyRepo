#include <iostream>
#include <random>
#include <limits>
#include <fstream>

struct TreapNode {
    int key;
    int priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(int k) : key(k), priority(std::rand()), 
                       left(nullptr), right(nullptr) {}
};

void split(TreapNode* root, int key, TreapNode*& left, TreapNode*& right) {
    if (!root) {
        left = nullptr;
        right = nullptr;
    } else if (root->key <= key) {
        split(root->right, key, root->right, right);
        left = root;
    } else {
        split(root->left, key, left, root->left);
        right = root;
    }
}

TreapNode* merge(TreapNode* left, TreapNode* right) {
    if (!left || !right) {
        return left ? left : right;
    }

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

TreapNode* erase(TreapNode* root, int key) {
    TreapNode* left, * right;
    split(root, key - 1, left, right);
    TreapNode* toDelete;
    split(right, key, toDelete, right);
    delete toDelete;
    return merge(left, right);
}

bool search(TreapNode* root, int key) {
    if (!root) {
        return false;
    } else if (root->key == key) {
        return true;
    } else if (root->key < key) {
        return search(root->right, key);
    } else {
        return search(root->left, key);
    }
}

TreapNode* insert(TreapNode* root, int key) {
    if (search(root, key)) {
        return root;
    }
    TreapNode* newNode = new TreapNode(key);
    TreapNode* left, * right;
    split(root, key, left, right);
    return merge(merge(left, newNode), right);
}

long sum(TreapNode* root, long l, long r) {
    long total = 0L;
    if (!root) return total;
    if (root->key < l) {
        total = (total + sum(root->right, l, r));
    } else if (root->key > r) {
        total = (total + sum(root->left, l, r));
    } else {
        total = (total + root->key);
        total = (total + sum(root->left, l, r));
        total = (total + sum(root->right, l, r));
    }
    return total;
}

int main() {
    TreapNode* treap = nullptr;
    int n;
    std::cin >> n;

    long prev = 0;
    for (int i = 0; i < n; i++) {
        char cmd;
        std::cin >> cmd;
        if (cmd == '?') {
            long l, r;
            std::cin >> l >> r;
            prev = sum(treap, l, r);
            std::cout << prev << std::endl;
        } else {
            long k;
            std::cin >> k;
            treap = insert(treap, (k + prev) % 1000000000);
            prev = 0;
        }
    }
}
