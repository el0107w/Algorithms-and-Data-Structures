#include <iostream>
#include <string>  
#include <utility>  
#include "Vector.h"

using namespace std;

// Функция для вывода вектора (демонстрация итераторов)
void printVector(const Vector<int>& v, const string& title) {
	cout << title << ": [";

	for (auto iterator = v.begin(); iterator != v.end(); ++iterator) {
		cout << *iterator;
		if (iterator + 1 != v.end()) {
			cout << ", ";
		}
	}
	cout << "]" << endl;
}

int main() {
	setlocale(LC_ALL, "");
	
	cout << "1. Демонстрация базовых методов и итераторов" << endl;

	Vector<int> v;
	v.push_back(812);
	v.push_back(66);
	v.push_back(7);
	v.push_back(17);
	v.push_back(67);
	v.push_back(11);

	printVector(v, "Исходный вектор (через итераторы)"); 
	
	cout << "Через range-based for: ";
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;

	cout << "\n2. Демонстрация быстрой сортировки" << endl;
	v.sort();
	printVector(v, "После быстрой сортировки");

	cout << "\n3. Демонстрация правила пяти" << endl;

	// Конструктор копирования
	Vector<int> v_copy = v;
	printVector(v_copy, "Копия (конструктор копирования)");

	// Конструктор перемещения
	Vector<int> v_move = std::move(v_copy); 
	printVector(v_move, "Перемещенный вектор");
	cout << "Размер v_copy после перемещения: " << v_copy.size() << endl;

	// Оператор присваивания копированием
	Vector<int> v_assign;
	v_assign = v_move;
	printVector(v_assign, "Присваивание копированием");

	// Оператор присваивания перемещением
	Vector<int> v_move_assign;
	v_move_assign = std::move(v_assign);
	printVector(v_move_assign, "Присваивание перемещением");

	cout << "\n4. Демонстрация роста ёмкости (амортизация)" << endl;
	Vector<int> capacityIncrease;
	
	for (int i = 1; i <= 10; i++) {
		capacityIncrease.push_back(i);
		cout << "push_back(" << i << "): size=" << capacityIncrease.size() 
		     << ", capacity=" << capacityIncrease.capacity() << endl;
	}
	
	return 0;
}