#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class RingBuffer {
private:
	T* data;
	size_t start;
	size_t end;
	size_t count;
	size_t capacity;
public:
	RingBuffer(size_t cap) : capacity(cap), start(0), end(0), count(0) {
		if (capacity == 0)
			throw invalid_argument("Объём должен быть больше 0");
		data = new T[capacity];
	}

	~RingBuffer() {
		delete[] data;
	}

	RingBuffer(const RingBuffer&) = delete;
	RingBuffer& operator=(const RingBuffer&) = delete;

	// Добавление элемента
	void push(const T& value) {
		data[end] = value;
		end = (end + 1) % capacity;

		if (count == capacity)
			start = (start + 1) % capacity;
		else
			count++;
	}

	// Извлечение элемента
	T pop() {
		if (isEmpty())
			throw underflow_error("Буфер пуст");

		T value = data[start];
		start = (start + 1) % capacity;
		count--;

		return value;
	}

	// Доступ по индексу
	T& operator[](size_t index) {
		if (index >= count)
			throw out_of_range("Индекс выходит за предел");
		return data[(start + index) % capacity];
	}

	const T& operator[](size_t index) const {
		if (index >= count)
			throw out_of_range("Индекс выходит за предел");
		return data[(start + index) % capacity];
	}

	// Проверка на пустоту
	bool isEmpty() const {
		return count == 0;
	}

	// Проверка на заполненность
	bool isFull() const {
		return count == capacity;
	}

	// Текущий размер
	size_t size() const {
		return count;
	}
};
