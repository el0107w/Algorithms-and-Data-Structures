#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Tree.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    srand(time(0));

    cout << "ЧАСТЬ 1: Дерево и зеркальное отображение" << endl;
    BST tree1;

    // Построение дерева
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);
    tree1.insert(3);
    tree1.insert(7);
    tree1.insert(20);
    tree1.insert(6);
    tree1.insert(18);

    cout << "Прямой обход:       "; tree1.preOrder();
    cout << "Симметричный обход: "; tree1.inOrder();
    cout << "Обратный обход:     "; tree1.postOrder();
    cout << "Уровневый обход:    "; tree1.levelOrder();

    cout << "\nЗеркальное отображение" << endl;
    tree1.mirror();
    cout << "Симметричный обход после зеркала: "; tree1.inOrder();

    cout << "\nЧАСТЬ 2: Восстановление BST" << endl;
    BST tree2;

    // Правильное дерево
    tree2.insert(10);
    tree2.insert(5);
    tree2.insert(15);
    tree2.insert(3);
    tree2.insert(7);
    tree2.insert(12);
    tree2.insert(20);

    // Специально ломаем его (меняем 5 и 15)
    tree2.forceError();

    cout << "Дерево с ошибками (in-order): ";
    tree2.inOrder();

    tree2.recoverBST();

    cout << "Исправленное дерево (in-order): ";
    tree2.inOrder();
    cout << endl;

    cout << "ЧАСТЬ 3: Применение BST" << endl;
    BST tree3;

    cout << "Создание дерева из 20 случайных чисел: ";
    for (int i = 0; i < 20; i++) {
        int num = rand() % 100;
        cout << num << " ";
        tree3.insert(num);
    }
    cout << "\n\n";

    cout << "Симметричный обход (отсортированная последовательность):" << endl;
    tree3.inOrder();

    cout << "Минимальный элемент: " << tree3.getMin() << endl;
    cout << "Максимальный элемент: " << tree3.getMax() << endl;
    cout << "Высота дерева: " << tree3.getHeight() << endl << endl;

    int target;
    cout << "Введите элемент для удаления: ";
    cin >> target;

    tree3.remove(target);
    cout << "\nДерево после удаления (симметричный обход):" << endl;
    tree3.inOrder();

    return 0;
}