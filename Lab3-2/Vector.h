#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

template <typename T>
class Vector {
private:
	T* data;
	int sz;
	int cap;

	// Приватные методы для быстрой сортировки
	int separation(int low, int high) {
		T basisEl = data[high];
		int i = (low - 1);

		for (int j = low; j <= high - 1; j++) {
			if (data[j] < basisEl) {
				i++;
				std::swap(data[i], data[j]);
			}
		}
		std::swap(data[i + 1], data[high]);
		return (i + 1);
	}

	void quickSort(int low, int high) {
		if (low < high) {
			int basisIndex = separation(low, high);
			quickSort(low, basisIndex - 1);
			quickSort(basisIndex + 1, high);
		}
	}

public:
	// Конструкторы
	Vector() : data(nullptr), sz(0), cap(0) {}

	explicit Vector(int n) : sz(n), cap(n) {
		data = new T[cap];
	}

	Vector(int n, const T& value) : sz(n), cap(n) {
		data = new T[cap];
		for (int i = 0; i < sz; i++)
			data[i] = value;
	}

	// Правило пяти
	// 1. Конструктор копирования
	Vector(const Vector& other) : sz(other.sz), cap(other.cap) {
		data = new T[cap];
		for (int i = 0; i < sz; i++)
			data[i] = other.data[i];
	}

	// 2. Конструктор перемещения
	Vector(Vector&& other) noexcept : data(other.data), sz(other.sz), cap(other.cap) {
		other.data = nullptr;
		other.sz = 0;
		other.cap = 0;
	}

	// 3. Деструктор
	~Vector() {
		delete[] data;
	}

	// 4. Оператор присваивания копированием 
	Vector& operator=(const Vector& other) {
		if (this != &other) {
			Vector temp(other);
			swap(temp);
		}
		return *this;
	}

	// 5. Оператор присваивания перемещением
	Vector& operator=(Vector&& other) noexcept {
		if (this != &other) {
			delete[] data;
			data = other.data;
			sz = other.sz;
			cap = other.cap;
			other.data = nullptr;
			other.sz = 0;
			other.cap = 0;
		}
		return *this;
	}

	// Методы доступа 
	int size() const { return sz; }
	int capacity() const { return cap; }
	bool empty() const { return sz == 0; }

	// Управление памятью
	void reserve(int newCap) {
		if (newCap <= cap)
			return;
		T* newData = new T[newCap];

		for (int i = 0; i < sz; i++)
			newData[i] = data[i];

		delete[] data;
		data = newData;
		cap = newCap;
	}

	void push_back(const T& value) {
		if (sz >= cap)
			reserve(cap == 0 ? 1 : cap * 2);
		data[sz++] = value;
	}

	void pop_back() {
		if (empty())
			throw underflow_error("Vector is empty");
		sz--;
	}

	void swap(Vector& other) {
		std::swap(data, other.data);
		std::swap(sz, other.sz);
		std::swap(cap, other.cap);
	}

	// Операторы доступа
	T& operator[](int index) {
		if (index < 0 || index >= sz)
			throw out_of_range("Index out of range");
		return data[index];
	}

	const T& operator[](int index) const {
		if (index < 0 || index >= sz) {
			throw std::out_of_range("Index out of range");
		}
		return data[index];
	}

	// Итераторы
	T* begin() { return data; }
	T* end() { return data + sz; }
	const T* begin() const { return data; }
	const T* end() const { return data + sz; }

	// Публичный метод сортировки (Вариант 11)
	void sort() {
		if (sz > 1)
			quickSort(0, sz - 1);
	}
};