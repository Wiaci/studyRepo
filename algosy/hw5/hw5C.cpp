#include <iostream>
#include <cstdlib>
#include <random>
#include <sstream>

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

TreapNode* findMinGreater(TreapNode* root, int x) {
    if (!root) {
        return nullptr;
    }

    if (root->key <= x) {
        return findMinGreater(root->right, x);
    }

    TreapNode* minGreater = findMinGreater(root->left, x);
    return minGreater ? std::min(minGreater, root, [](const TreapNode* a, const TreapNode* b) {
        return a->key < b->key;
    }) : root;
}

TreapNode* findMaxSmaller(TreapNode* root, int x) {
    if (!root) {
        return nullptr;
    }

    if (root->key >= x) {
        return findMaxSmaller(root->left, x);
    }

    TreapNode* maxSmaller = findMaxSmaller(root->right, x);
    return maxSmaller ? std::max(maxSmaller, root, [](const TreapNode* a, const TreapNode* b) {
        return a->key < b->key;
    }) : root;
}

// Inorder traversal for debugging
void inorderTraversal(TreapNode* root) {
    if (root) {
        inorderTraversal(root->left);
        std::cout << "Key: " << root->key << ", Priority: " << root->priority << std::endl;
        inorderTraversal(root->right);
    }
}


int main() {
    TreapNode* treap = nullptr;

    std::string line;
    while (true) {
        try {
            std::getline(std::cin, line);
            if (line.empty()) {
                break;
            }

            std::istringstream iss(line);
            std::string operation;
            iss >> operation;

            int key = 0;
            if (iss >> key) {}

            if (operation == "insert") {
                treap = insert(treap, key);
            } else if (operation == "delete") {
                treap = erase(treap, key);
            } else if (operation == "exists") {
                std::cout << (search(treap, key) ? "true" : "false") << std::endl;
            } else if (operation == "next") {
                TreapNode* f = findMinGreater(treap, key);
                std::cout << (f ? std::to_string(f->key) : "none") << std::endl;
            } else if (operation == "prev") {
                TreapNode* f = findMaxSmaller(treap, key);
                std::cout << (f ? std::to_string(f->key) : "none") << std::endl;
            }

        } catch (const std::exception& e) {
            break;
        }
    }

    return 0;
}