#include <iostream>
#include <chrono>
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

using namespace std;
using namespace chrono;

int main() {
    setlocale(LC_ALL, "");

    cout << "1. Односвязный список" << endl;
    SinglyLinkedList<int> sList;

    // push_front для создания списка [1, 2, 3, 2, 1]
    sList.push_front(1);
    sList.push_front(2);
    sList.push_front(3);
    sList.push_front(2);
    sList.push_front(1);

    cout << "Создан список: "; sList.print();
    cout << "Размер (size): " << sList.size() << endl;
    cout << "Палиндром? " << (sList.checkMirror() ? "Да" : "Нет") << endl;

    // Демонстрация pop_front
    sList.pop_front();
    cout << "После pop_front: "; sList.print();
    cout << "Новый размер: " << sList.size() << endl << endl;


    cout << "Двусвязный список" << endl;
    DoublyLinkedList<int> dList;
    // Заполнение через push_back
    dList.push_back(10);
    dList.push_back(20);
    dList.push_back(30);
    dList.push_back(40);
    dList.push_back(50);

    cout << "Создан список: "; dList.print();
    dList.swapEls();
    cout << "После swapEls: "; dList.print();
    cout << endl;


    cout << "3. Сравнение производительности" << endl;
    const int N = 10000;

    // Тест: push_front (O(1) у обоих списков)
    auto start = high_resolution_clock::now();
    SinglyLinkedList<int> sTest;
    for (int i = 0; i < N; i++) sTest.push_front(i);
    auto end = high_resolution_clock::now();
    auto timeSLL_Push = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    DoublyLinkedList<int> dTest;
    for (int i = 0; i < N; i++) dTest.push_front(i);
    end = high_resolution_clock::now();
    auto timeDLL_Push = duration_cast<microseconds>(end - start).count();

    // Тест: pop_front (O(1) у обоих списков)
    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) sTest.pop_front();
    end = high_resolution_clock::now();
    auto timeSLL_Pop = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) dTest.pop_front();
    end = high_resolution_clock::now();
    auto timeDLL_Pop = duration_cast<microseconds>(end - start).count();

    cout << "Количество элементов: " << N << endl;
    cout << "Операция\t\tSinglyLinkedList\tDoublyLinkedList" << endl;
    cout << "push_front (мкс)\t" << timeSLL_Push << "\t\t\t" << timeDLL_Push << endl;
    cout << "pop_front (мкс)\t\t" << timeSLL_Pop << "\t\t\t" << timeDLL_Pop << endl;

    cout << "\nВывод: Вставка и удаление в начале (push_front, pop_front) в обоих списках выполняются за O(1) и требуют минимального времени, так как не требуют перебора элементов." << endl;

    return 0;
}