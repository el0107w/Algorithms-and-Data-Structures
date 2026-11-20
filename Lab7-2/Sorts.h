#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Глобальные счетчики для профилирования (ветвления и обмены)
extern long long comparisons;
extern long long swaps;

// Вспомогательная сортировка вставками
// Оптимизация ветвлений: для маленьких массивов вставки работают быстрее и предсказуемее
template <typename T>
void insertionSort(T arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= low) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                swaps++;
                j--;
            }
            else break;
        }
        arr[j + 1] = key;
    }
}

// 1. Быстрая сортировка (Quick Sort с медианой из трёх)
template <typename T>
void medianOfThree(T arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) { swap(arr[mid], arr[low]); swaps++; }
    if (arr[high] < arr[low]) { swap(arr[high], arr[low]); swaps++; }
    if (arr[high] < arr[mid]) { swap(arr[high], arr[mid]); swaps++; }
    swap(arr[mid], arr[high - 1]);
    swaps++;
}

template <typename T>
int partition(T arr[], int low, int high) {
    medianOfThree(arr, low, high);
    T pivot = arr[high - 1];
    int i = low;
    int j = high - 1;

    while (true) {
        while (arr[++i] < pivot) comparisons++;
        while (arr[--j] > pivot) comparisons++;
        if (i >= j) break;
        swap(arr[i], arr[j]);
        swaps++;
    }
    swap(arr[i], arr[high - 1]);
    swaps++;
    return i;
}

template <typename T>
void quickSort(T arr[], int low, int high) {
    // Оптимизация: для малых подмассивов используем вставки (меньше рекурсии и ветвлений)
    if (high - low < 15) {
        insertionSort(arr, low, high);
        return;
    }

    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Обертка для единого интерфейса вызова
template <typename T>
void quickSortWrapper(T arr[], int n) {
    quickSort(arr, 0, n - 1);
}

// 2. Сортировка слиянием (Merge Sort с оптимизацией памяти)
template <typename T>
void merge(T arr[], T temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        comparisons++;
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left; i <= right; i++) arr[i] = temp[i];
}

template <typename T>
void mergeSortHelper(T arr[], T temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, temp, left, mid);
        mergeSortHelper(arr, temp, mid + 1, right);
        merge(arr, temp, left, mid, right);
    }
}

template <typename T>
void mergeSort(T arr[], int n) {
    // Оптимизация КЭШа: Выделяем память один раз, а не в каждом рекурсивном вызове
    T* temp = new T[n];
    mergeSortHelper(arr, temp, 0, n - 1);
    delete[] temp;
}

// 3. Пирамидальная сортировка (Heap Sort)
// Оптимизация: итеративный heapify (без рекурсии, защита стека)
template <typename T>
void heapify(T arr[], int n, int i) {
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n) {
            comparisons++;
            if (arr[left] > arr[largest]) largest = left;
        }
        if (right < n) {
            comparisons++;
            if (arr[right] > arr[largest]) largest = right;
        }

        if (largest == i) break;

        swap(arr[i], arr[largest]);
        swaps++;
        i = largest;
    }
}

template <typename T>
void heapSort(T arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        swaps++;
        heapify(arr, i, 0);
    }
}