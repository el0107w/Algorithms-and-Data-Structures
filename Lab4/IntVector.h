#pragma once
#include <iostream>

class IntVector {
private:
	int* data;
	int size;
	int capacity;

public:
	IntVector();
	IntVector(int n);
	IntVector(const IntVector& other);
	IntVector(IntVector&& other) noexcept;

	~IntVector();

	IntVector& operator=(const IntVector& other);
	IntVector& operator=(IntVector&& other) noexcept;

	int& operator[](int index);
	const int& operator[](int index) const;

	int getSize() const;
	int getCapacity() const;
	bool isEmpty() const;

	void pushBack(int value);
	void popBack();
	void print() const;

	void reserve(int newCapacity);
	void shrinkToFit();

	using iterator = int*;
	using const_iterator = const int*;

	iterator begin() { return data; }
	iterator end() { return data + size; }
	const_iterator begin() const { return data; }
	const_iterator end() const { return data + size; }

	iterator insert(iterator pos, int value);
};