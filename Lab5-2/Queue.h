#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    T* data;
    int frontIndex, rearIndex, count, capacity;
    void resize() {
        int oldCapacity = capacity;
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[(frontIndex + i) % oldCapacity];
        }
        delete[] data;
        data = newData;
        frontIndex = 0;
        rearIndex = count;
    }
public:
    Queue(int cap = 10) : capacity(cap), frontIndex(0), rearIndex(0), count(0) { data = new T[capacity]; }
    ~Queue() { delete[] data; }
    void enqueue(const T& val) {
        if (count >= capacity) resize();
        data[rearIndex] = val;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }
    T dequeue() {
        if (isEmpty()) throw underflow_error("Queue is empty");
        T val = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return val;
    }
    T front() const {
        if (isEmpty()) throw underflow_error("Queue is empty");
        return data[frontIndex];
    }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

template <typename T>
Queue<T> mergeQueues(Queue<T>& q1, Queue<T>& q2) {
    Queue<T> result;
    while (!q1.isEmpty() || !q2.isEmpty()) {
        if (!q1.isEmpty()) result.enqueue(q1.dequeue());
        if (!q2.isEmpty()) result.enqueue(q2.dequeue());
    }
    return result;
}