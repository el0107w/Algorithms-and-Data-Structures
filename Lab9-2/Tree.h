#pragma once
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // Вспомогательные рекурсивные функции
    Node* insertHelper(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        if (key < node->data) node->left = insertHelper(node->left, key);
        else if (key > node->data) node->right = insertHelper(node->right, key);
        return node;
    }

    bool searchHelper(Node* node, int key) {
        if (node == nullptr) return false;
        if (node->data == key) return true;
        if (key < node->data) return searchHelper(node->left, key);
        return searchHelper(node->right, key);
    }

    Node* findMinNode(Node* node) {
        while (node && node->left != nullptr) node = node->left;
        return node;
    }

    Node* removeHelper(Node* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->data) node->left = removeHelper(node->left, key);
        else if (key > node->data) node->right = removeHelper(node->right, key);
        else {
            // Случай 1: лист
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Случай 2: один потомок
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Случай 3: два потомка
            else {
                Node* temp = findMinNode(node->right);
                node->data = temp->data;
                node->right = removeHelper(node->right, temp->data);
            }
        }
        return node;
    }

    // Обходы
    void preOrderHelper(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
    void inOrderHelper(Node* node) {
        if (!node) return;
        inOrderHelper(node->left);
        cout << node->data << " ";
        inOrderHelper(node->right);
    }
    void postOrderHelper(Node* node) {
        if (!node) return;
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->data << " ";
    }

    // Зеркальное отображение
    void mirrorHelper(Node* node) {
        if (!node) return;
        swap(node->left, node->right);
        mirrorHelper(node->left);
        mirrorHelper(node->right);
    }

    int heightHelper(Node* node) {
        if (!node) return 0;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }

    // Восстановление BST
    void recoverHelper(Node* node, Node*& prev, Node*& first, Node*& middle, Node*& last) {
        if (!node) return;
        recoverHelper(node->left, prev, first, middle, last);

        if (prev && node->data < prev->data) {
            if (!first) {
                first = prev;
                middle = node;
            }
            else {
                last = node;
            }
        }
        prev = node;
        recoverHelper(node->right, prev, first, middle, last);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    // Обязательные операции
    void insert(int key) { root = insertHelper(root, key); }
    bool search(int key) { return searchHelper(root, key); }
    void remove(int key) { root = removeHelper(root, key); }

    // Обходы
    void preOrder() { preOrderHelper(root); cout << endl; }
    void inOrder() { inOrderHelper(root); cout << endl; }
    void postOrder() { postOrderHelper(root); cout << endl; }
    void levelOrder() {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
    }

    // Дополнительные задания
    void mirror() {
        mirrorHelper(root);
        cout << "Дерево зеркально отображено!" << endl;
    }

    // Ломает дерево, меняя местами два узла
    void forceError() {
        if (root && root->left && root->right) {
            swap(root->left->data, root->right->data);
        }
    }

    void recoverBST() {
        Node* prev = nullptr, * first = nullptr, * middle = nullptr, * last = nullptr;
        recoverHelper(root, prev, first, middle, last);

        // Если есть last, значит узлы не соседние. Если нет - соседние.
        if (first && last) swap(first->data, last->data);
        else if (first && middle) swap(first->data, middle->data);
    }

    // Для 3-й части
    int getHeight() { return heightHelper(root); }
    int getMin() { return findMinNode(root)->data; }
    int getMax() {
        Node* curr = root;
        while (curr && curr->right) curr = curr->right;
        return curr->data;
    }
};