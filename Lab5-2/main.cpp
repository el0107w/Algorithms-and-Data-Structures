#include <iostream>
#include <vector>
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "PriorityQueue.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    cout << "1. Стек: Инфикс в Постфикс" << endl;
    string expr = "(A+B)*C-D";
    cout << "Инфикс: " << expr << endl;
    cout << "Постфикс: " << infixToPostfix(expr) << endl << endl;

    cout << "2. Очередь: Чередование двух очередей" << endl;
    Queue<int> q1, q2;
    q1.enqueue(1); q1.enqueue(3); q1.enqueue(5);
    q2.enqueue(2); q2.enqueue(4); q2.enqueue(6); q2.enqueue(8);
    cout << "Очередь 1: 1 3 5" << endl;
    cout << "Очередь 2: 2 4 6 8" << endl;
    Queue<int> merged = mergeQueues(q1, q2);
    cout << "Объединенная: ";
    while (!merged.isEmpty()) cout << merged.dequeue() << " ";
    cout << endl << endl;

    cout << "3. Дек: Скользящее окно (минимумы)" << endl;
    vector<int> arr = { 1, 3, -1, -3, 5, 3, 6, 7 };
    int k = 3;
    cout << "Массив: 1, 3, -1, -3, 5, 3, 6, 7" << endl;
    slidingWindowMin(arr, k);
    cout << endl;

    cout << "4. Приоритетная очередь (Фикс. ёмкость)" << endl;
    PriorityQueue<int> pq(3); 
    pq.push(10);
    pq.push(20);
    pq.push(30);
    pq.push(40);
    cout << "Максимум (top): " << pq.top() << endl;
    cout << "Извлечение: " << pq.pop() << endl;
    cout << "Новый максимум: " << pq.top() << endl;

    return 0;
}