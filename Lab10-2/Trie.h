#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Trie {
private:
    struct TrieNode {
        TrieNode* children[36]; // 26 букв + 10 цифр
        bool isEndOfWord;

        TrieNode() : isEndOfWord(false) {
            for (int i = 0; i < 36; i++) children[i] = nullptr;
        }
    };
    TrieNode* root;

    // Поддержка цифр (0-9)
    int getIndex(char ch) {
        if (ch >= 'a' && ch <= 'z') return ch - 'a';
        if (ch >= '0' && ch <= '9') return ch - '0' + 26;
        return -1; // Недопустимый символ
    }

    void destroy(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 36; i++) destroy(node->children[i]);
        delete node;
    }

    void collect(TrieNode* node, string current, vector<string>& result) {
        if (node->isEndOfWord) result.push_back(current);
        for (int i = 0; i < 36; i++) {
            if (node->children[i]) {
                char ch = (i < 26) ? ('a' + i) : ('0' + (i - 26));
                collect(node->children[i], current + ch, result);
            }
        }
    }

public:
    Trie() { root = new TrieNode(); }
    ~Trie() { destroy(root); }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = getIndex(ch);
            if (index == -1) continue;
            if (!current->children[index]) current->children[index] = new TrieNode();
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = getIndex(ch);
            if (index == -1 || !current->children[index]) return false;
            current = current->children[index];
        }
        return current->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            int index = getIndex(ch);
            if (index == -1 || !current->children[index]) return false;
            current = current->children[index];
        }
        return true;
    }

    vector<string> getWordsByPrefix(const string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            int index = getIndex(ch);
            if (index == -1 || !current->children[index]) return {};
            current = current->children[index];
        }
        vector<string> result;
        collect(current, prefix, result);
        return result;
    }
};