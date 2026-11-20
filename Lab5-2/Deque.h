#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Deque {
private:
    T* data;
    int frontIndex, rearIndex, count, capacity;
    void resize() {
        int oldCapacity = capacity;
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < count; i++) newData[i] = data[(frontIndex + i) % oldCapacity];
        delete[] data;
        data = newData;
        frontIndex = 0;
        rearIndex = count;
    }
public:
    Deque(int cap = 10) : capacity(cap), frontIndex(0), rearIndex(0), count(0) { data = new T[capacity]; }
    ~Deque() { delete[] data; }

    void push_front(const T& val) {
        if (count >= capacity) resize();
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        data[frontIndex] = val;
        count++;
    }
    void push_back(const T& val) {
        if (count >= capacity) resize();
        data[rearIndex] = val;
        rearIndex = (rearIndex + 1) % capacity;
        count++;
    }
    T pop_front() {
        if (isEmpty()) throw underflow_error("Deque is empty");
        T val = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return val;
    }
    T pop_back() {
        if (isEmpty()) throw underflow_error("Deque is empty");
        rearIndex = (rearIndex - 1 + capacity) % capacity;
        T val = data[rearIndex];
        count--;
        return val;
    }
    T front() const {
        if (isEmpty()) throw underflow_error("Deque is empty");
        return data[frontIndex];
    }
    T back() const {
        if (isEmpty()) throw underflow_error("Deque is empty");
        return data[(rearIndex - 1 + capacity) % capacity];
    }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

inline void slidingWindowMin(const vector<int>& arr, int k) {
    Deque<int> dq;
    cout << "Минимумы для k=" << k << ": ";
    for (int i = 0; i < arr.size(); i++) {
        while (!dq.isEmpty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.isEmpty() && arr[dq.back()] >= arr[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) cout << arr[dq.front()] << " ";
    }
    cout << endl;
}