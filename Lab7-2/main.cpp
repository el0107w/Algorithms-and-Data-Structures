#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include "Sorts.h"

using namespace std;
using namespace chrono;

long long comparisons = 0;
long long swaps = 0;

string randomString(int length) {
    string str = "";
    for (int i = 0; i < length; i++) str += char(rand() % 26 + 'a');
    return str;
}

template <typename T>
void testSort(string name, void (*sortFunc)(T[], int), T originalArr[], int n) {
    T* arr = new T[n];
    for (int i = 0; i < n; i++) arr[i] = originalArr[i];

    comparisons = 0;
    swaps = 0;

    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<microseconds>(end - start).count();

    cout << "  " << name << ":\t" << time << " мкс\t(Сравнений: " << comparisons << ", Обменов: " << swaps << ")\n";
    delete[] arr;
}

template <typename T>
void runAllSorts(string typeName, T originalArr[], int n) {
    cout << "Тип данных: " << typeName << " (N = " << n << ")" << endl;
    testSort<T>("Быстрая (Quick)", quickSortWrapper<T>, originalArr, n);
    testSort<T>("Слиянием (Merge)", mergeSort<T>, originalArr, n);
    testSort<T>("Пирамидальная (Heap)", heapSort<T>, originalArr, n);
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(0));

    const int N = 1000;

    int* intArr = new int[N];
    for (int i = 0; i < N; i++) intArr[i] = rand() % 10000;
    runAllSorts("int", intArr, N);
    delete[] intArr;

    double* dblArr = new double[N];
    for (int i = 0; i < N; i++) dblArr[i] = (rand() % 10000) / 100.0;
    runAllSorts("double", dblArr, N);
    delete[] dblArr;

    string* strArr = new string[N];
    for (int i = 0; i < N; i++) strArr[i] = randomString(5);
    runAllSorts("string", strArr, N);
    delete[] strArr;

    return 0;
}