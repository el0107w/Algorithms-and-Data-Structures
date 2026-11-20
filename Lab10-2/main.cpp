#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "AVL.h"
#include "BST.h"
#include "Trie.h"

using namespace std;
using namespace chrono;

int main() {
    setlocale(LC_ALL, "");
    srand(time(0));

    cout << "1. AVL-дерево" << endl;
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    cout << "Поиск 25: " << (avl.search(25) ? "найден" : "не найден") << endl;
    cout << "Поиск 99: " << (avl.search(99) ? "найден" : "не найден") << endl;

    cout << "Высота AVL-дерева: " << avl.getHeight() << endl;
    cout << "Проверка сбалансированности (isBalanced): " << (avl.isBalanced() ? "Сбалансировано" : "НЕ сбалансировано") << endl;

    avl.remove(30);
    cout << "После удаления 30, дерево сбалансировано? " << (avl.isBalanced() ? "Да" : "Нет") << endl << endl;

    cout << "2. Trie" << endl;
    Trie trie;
    trie.insert("user123");
    trie.insert("user456");
    trie.insert("admin99");
    trie.insert("apple");

    cout << "Поиск 'user123': " << (trie.search("user123") ? "найден" : "не найден") << endl;
    cout << "Поиск 'user999': " << (trie.search("user999") ? "найден" : "не найден") << endl;
    cout << "Префикс 'user': " << (trie.startsWith("user") ? "true" : "false") << endl;
    cout << "Префикс 'adm': " << (trie.startsWith("adm") ? "true" : "false") << endl;

    vector<string> userWords = trie.getWordsByPrefix("user");
    cout << "Слова по префиксу 'user': ";
    for (const auto& w : userWords) cout << w << " ";
    cout << "\n\n";

    cout << "3. Сравнительный анализ BST и AVL" << endl;
    vector<int> sizes = { 1000, 5000, 10000 };

    cout << "Случайные данные" << endl;
    cout << setw(10) << "N" << setw(20) << "BST insert (мкс)" << setw(20) << "AVL insert (мкс)" << endl;

    for (int N : sizes) {
        vector<int> arr(N);
        for (int i = 0; i < N; i++) arr[i] = rand() % (N * 10); // Случайные

        BST bst;
        auto start = high_resolution_clock::now();
        for (int x : arr) bst.insert(x);
        auto end = high_resolution_clock::now();
        auto timeBST = duration_cast<microseconds>(end - start).count();

        AVLTree avlTree;
        start = high_resolution_clock::now();
        for (int x : arr) avlTree.insert(x);
        end = high_resolution_clock::now();
        auto timeAVL = duration_cast<microseconds>(end - start).count();

        cout << setw(10) << N << setw(20) << timeBST << setw(20) << timeAVL << endl;
    }

    cout << "\nОтсортированные данные (Худший случай для BST)" << endl;
    cout << setw(10) << "N" << setw(20) << "BST insert (мкс)" << setw(20) << "AVL insert (мкс)" << endl;

    for (int N : sizes) {
        vector<int> arr(N);
        for (int i = 0; i < N; i++) arr[i] = i; // Отсортированные по возрастанию

        BST bst;
        auto start = high_resolution_clock::now();
        for (int x : arr) bst.insert(x);
        auto end = high_resolution_clock::now();
        auto timeBST = duration_cast<microseconds>(end - start).count();

        AVLTree avlTree;
        start = high_resolution_clock::now();
        for (int x : arr) avlTree.insert(x);
        end = high_resolution_clock::now();
        auto timeAVL = duration_cast<microseconds>(end - start).count();

        cout << setw(10) << N << setw(20) << timeBST << setw(20) << timeAVL << endl;
    }

    return 0;
}