#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
	T* data;
	int topIndex;
	int capacity;
	void resize() {
		capacity *= 2;
		T* newData = new T[capacity];
		for (int i = 0; i <= topIndex; i++)
			newData[i] = data[i];
		delete[] data;
		data = newData;
	}
public:
	Stack(int cap = 10) :capacity(cap), topIndex(-1) {
		data = new T[capacity];
	}
	~Stack() {
		delete[] data;
	}

	void push(const T& val) {
		if (topIndex >= capacity - 1)
			resize();
		data[++topIndex] = val;
	}
    T pop() {
        if (isEmpty()) throw underflow_error("Stack is empty");
        return data[topIndex--];
    }
    T top() const {
        if (isEmpty()) throw underflow_error("Stack is empty");
        return data[topIndex];
    }
    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }
};

// Сортировочная станция (Инфикс -> Постфикс)
inline int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

inline string infixToPostfix(const string& expr) {
    Stack<char> st;
    string result = "";
    for (char c : expr) {
        if (isalnum(c)) result += c; 
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (!st.isEmpty() && st.top() != '(') {
                result += st.pop();
            }
            st.pop(); 
        }
        else { 
            while (!st.isEmpty() && getPriority(st.top()) >= getPriority(c)) {
                result += st.pop();
            }
            st.push(c);
        }
    }
    while (!st.isEmpty()) result += st.pop();
    return result;
};