#include <iostream>
#include <chrono>
#include <ctime>
#include "Recursion.h"
#include "Sorting.h"

using namespace std;
using namespace chrono;

long long measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    int* copy = new int[n];
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    auto start = high_resolution_clock::now();
    sortFunc(copy, n);
    auto end = high_resolution_clock::now();

    delete[] copy;
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(0)); 

    cout << "ЧАСТЬ 1: РЕКУРСИЯ\n" << endl;
    cout << "Факториал 10 (рекурсивно): " << factorialRec(10) << endl;
    cout << "Фибоначчи 20 (рекурсивно): " << fibRec(20) << "\n" << endl;

    cout << "Обход лабиринта (6x6)" << endl;
    if (solveMaze(0, 0)) {
        cout << "Путь найден (*):" << endl;
        printMaze();
    }
    else {
        cout << "Путь не найден!" << endl;
    }

    cout << "\nЗадача о ферзях (5x5)" << endl;
    if (solveNQueens(0)) {
        printQueens();
    }
    else {
        cout << "Решений нет!" << endl;
    }
    cout << "\n";

    cout << "ЧАСТЬ 2: СОРТИРОВКИ\n" << endl;
    const int N = 1000;
    int* originalArr = new int[N];
    for (int i = 0; i < N; i++) originalArr[i] = rand() % 10000;

    cout << "Сравнение производительности (N = " << N << "):" << endl;
    cout << "Рекурсивная пузырьковая: " << measureTime(bubbleSortRecursive, originalArr, N) << " мкс" << endl;
    cout << "Итеративная выбором:     " << measureTime(selectionSort, originalArr, N) << " мкс" << endl;

    delete[] originalArr;
    return 0;
}