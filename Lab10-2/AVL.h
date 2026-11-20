#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) { return node ? node->height : 0; }
    int balanceFactor(AVLNode* node) { return node ? height(node->left) - height(node->right) : 0; }
    void updateHeight(AVLNode* node) { if (node) node->height = 1 + max(height(node->left), height(node->right)); }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* balance(AVLNode* node) {
        if (!node) return node;
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0) node->left = leftRotate(node->left); // LR
            return rightRotate(node); // LL
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0) node->right = rightRotate(node->right); // RL
            return leftRotate(node); // RR
        }
        return node;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;
        return balance(node);
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    AVLNode* remove(AVLNode* node, int key) {
        if (!node) return node;
        if (key < node->key) node->left = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) { temp = node; node = nullptr; }
                else *node = *temp;
                delete temp;
            }
            else {
                AVLNode* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }
        if (!node) return node;
        return balance(node);
    }

    bool search(AVLNode* node, int key) {
        if (!node) return false;
        if (node->key == key) return true;
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }

    // Проверка сбалансированности
    bool isBalanced(AVLNode* node) {
        if (!node) return true;
        int bf = abs(height(node->left) - height(node->right));
        return (bf <= 1) && isBalanced(node->left) && isBalanced(node->right);
    }

    void destroy(AVLNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }
    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = remove(root, key); }
    bool search(int key) { return search(root, key); }
    bool isBalanced() { return isBalanced(root); }
    int getHeight() { return height(root); }
};