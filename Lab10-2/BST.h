#pragma once
#include <iostream>
#include <queue>
using namespace std;

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // Итеративное удаление (чтобы не было Stack Overflow)
    void destroy(BSTNode* node) {
        if (!node) return;
        queue<BSTNode*> q;
        q.push(node);
        while (!q.empty()) {
            BSTNode* curr = q.front();
            q.pop();
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
            delete curr;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    // Итеративная вставка
    void insert(int key) {
        BSTNode* newNode = new BSTNode(key);
        if (!root) {
            root = newNode;
            return;
        }
        BSTNode* current = root;
        BSTNode* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (key < current->key) current = current->left;
            else if (key > current->key) current = current->right;
            else { delete newNode; return; } 
        }

        if (key < parent->key) parent->left = newNode;
        else parent->right = newNode;
    }

    // Итеративный поиск
    bool search(int key) {
        BSTNode* current = root;
        while (current != nullptr) {
            if (key == current->key) return true;
            if (key < current->key) current = current->left;
            else current = current->right;
        }
        return false;
    }
};