#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PriorityQueue {
private:
    T* heap;
    int count, capacity, maxCapacity;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else break;
        }
    }
    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;
            if (left < count && heap[left] > heap[largest]) largest = left;
            if (right < count && heap[right] > heap[largest]) largest = right;
            if (largest == index) break;
            swap(heap[index], heap[largest]);
            index = largest;
        }
    }
public:
    PriorityQueue(int maxCap) : maxCapacity(maxCap), count(0), capacity(maxCap) {
        heap = new T[capacity];
    }
    ~PriorityQueue() { delete[] heap; }

    void push(const T& value) {
        if (count < maxCapacity) {
            heap[count] = value;
            heapifyUp(count);
            count++;
        }
        else if (value > heap[0]) {
            // ќчередь полна, но новый элемент больше минимального (корн€)
            heap[0] = value;
            heapifyDown(0);
            cout << "ќчередь полна. Ёлемент " << value << " заменил минимальный." << endl;
        }
        else {
            cout << "ќчередь полна. Ёлемент " << value << " отброшен." << endl;
        }
    }
    T pop() {
        if (isEmpty()) throw underflow_error("PriorityQueue is empty");
        T root = heap[0];
        heap[0] = heap[count - 1];
        count--;
        heapifyDown(0);
        return root;
    }
    T top() const {
        if (isEmpty()) throw underflow_error("PriorityQueue is empty");
        return heap[0];
    }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};