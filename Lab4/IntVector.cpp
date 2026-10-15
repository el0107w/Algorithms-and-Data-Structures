#include "IntVector.h"
#include <stdexcept>

IntVector::IntVector() : size(0), capacity(10) {
	data = new int[capacity];
}

IntVector::IntVector(int n) : size(n), capacity(n) {
	if (n < 0)
		throw std::invalid_argument("Размер не может быть отрицательным");
	if (n == 0)
		capacity = 1;

	data = new int[capacity];

	for (int i = 0; i < size; i++)
		data[i] = 0;
}

IntVector::IntVector(const IntVector& other) : size(other.size), capacity(other.capacity){
	data = new int[capacity];

	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
}

IntVector::IntVector(IntVector&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

IntVector::~IntVector() {
	delete[] data;
}

IntVector& IntVector::operator=(const IntVector& other) {
	if (this != &other) {
		int* newData = new int[other.capacity];

		for (int i = 0; i < other.size; i++)
			newData[i] = other.data[i];
		
		delete[] data;
		data = newData;
		size = other.size;
		capacity = other.capacity;
	}
	return *this;
}

IntVector& IntVector::operator=(IntVector&& other) noexcept {
	if (this != &other) {
		delete[] data;
		data = other.data;
		size = other.size;
		capacity = other.capacity;
		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;
	}
	return *this;
}

int& IntVector::operator[](int index) {
	if (index < 0 || index >= size)
		throw std::out_of_range("Индекс вне диапазона");

	return data[index];
}

const int& IntVector::operator[](int index) const {
	if (index < 0 || index >= size)
		throw std::out_of_range("Индекс вне диапазона");

	return data[index];
}

int IntVector::getSize() const { return size; }
int IntVector::getCapacity() const { return capacity; }
bool IntVector::isEmpty() const { return size == 0; }

void IntVector::pushBack(int value) {
	if (size >= capacity) {
		int newCapacity = capacity * 2;
		int* newData = new int[newCapacity];

		for (int i = 0; i < size; i++)
			newData[i] = data[i];

		delete[] data;
		data = newData;
		capacity = newCapacity;
	}
	data[size] = value;
	size++;
}

void IntVector::popBack() {
	if (isEmpty())
		throw std::underflow_error("Вектор пуст");
	size--;
}

void IntVector::print() const {
	std::cout << "[";

	for (int i = 0; i < size; i++) {
		std::cout << data[i];
		if (i < size - 1)
			std::cout << ", ";
	}
	std::cout << "]\n";
}

void IntVector::reserve(int newCapacity) {
	if (newCapacity <= capacity)
		return;

	int* newData = new int[newCapacity];

	for (int i = 0; i < size; i++)
		newData[i] = data[i];

	delete[] data;
	data = newData;
	capacity = newCapacity;
}

void IntVector::shrinkToFit() {
	if (capacity == size)
		return;

	int* newData = new int[size];

	for (int i = 0; i < size; i++)
		newData[i] = data[i];

	delete[] data;
	data = newData;
	capacity = size;
}

IntVector::iterator IntVector::insert(iterator pos, int value) {
	int index = pos - data;

	if (index<0 || index > size)
		throw std::out_of_range("Позиция вне диапазона");

		if (size >= capacity) {
			int newCapacity = capacity * 2;
			int* newData = new int[newCapacity];

			for (int i = 0; i < size; i++)
				newData[i] = data[i];

			delete[] data;
			data = newData;
			capacity = newCapacity;
		}
		for (int i = size; i > index; i--)
			data[i] = data[i - 1];

		data[index] = value;
		size++;

		return data + index;
}