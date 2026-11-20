#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

// Задание 11: Рекурсивная пузырьковая сортировка
inline void bubbleSortRecursive(int arr[], int n) {
    if (n == 1) return;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) swap(arr[i], arr[i + 1]);
    }
    bubbleSortRecursive(arr, n - 1);
}

// Сортировка выбором (итеративная)
inline void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        if (minIndex != i) swap(arr[i], arr[minIndex]);
    }
}