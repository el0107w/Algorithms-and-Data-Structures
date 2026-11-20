#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "HashTable.h"

using namespace std;
using namespace chrono;

// Задание 11: Двоичный поиск в массиве, отсортированном по убыванию
int binarySearchDescending(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        // В убывающем массиве: если средний меньше искомого, ищем левее
        if (arr[mid] < target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(0));

    cout << "Сравнение производительности поиска (Вариант 11)" << endl;
    cout << setw(10) << "N" << setw(20) << "Бинарный поиск (мкс)" << setw(20) << "Хеш-таблица (мкс)" << endl;

    // Размеры массивов для теста
    vector<int> testSizes = { 1000, 10000, 100000 };
    const int QUERIES = 1000;

    for (int N : testSizes) {
        // 1. Подготовка массива для бинарного поиска (по убыванию)
        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            arr[i] = N - i;
        }

        // 2. Подготовка хеш-таблицы (размер чуть больше N, чтобы избежать коллизий)
        HashTable ht(N * 1.5);
        for (int i = 0; i < N; i++) {
            ht.insert(arr[i], Student("Student_" + to_string(i), (i % 4) + 1));
        }

        // Генерирование 1000 случайных ключей для поиска
        vector<int> queries(QUERIES);
        for (int i = 0; i < QUERIES; i++) {
            queries[i] = rand() % (N + 1);
        }

        // 3. Замер времени бинарного поиска
        auto start = high_resolution_clock::now();
        for (int q : queries) {
            binarySearchDescending(arr, q);
        }
        auto end = high_resolution_clock::now();
        auto timeBinary = duration_cast<microseconds>(end - start).count();

        // 4. Замер времени поиска в хеш-таблице
        start = high_resolution_clock::now();
        for (int q : queries) {
            ht.find(q);
        }
        end = high_resolution_clock::now();
        auto timeHash = duration_cast<microseconds>(end - start).count();

        // Вывод результатов для текущего N
        cout << setw(10) << N << setw(20) << timeBinary << setw(20) << timeHash << endl;
    }

    return 0;
}