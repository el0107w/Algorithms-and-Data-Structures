#pragma once
#include <iostream>
#include <vector>
#include "Bus.h"

using namespace std;

class Depot {
private:
	static Depot* singleton;					// Статический указатель для Одиночки
	vector<Bus*> bus;							// Агрегация

	Depot();									// Приватный конструктор
public:
	Depot(const Depot&) = delete;				// Запрет копирования
	Depot& operator=(const Depot&) = delete;

	static Depot* getSingleton();				// Точка доступа
	void addBus(Bus* b);
	void printAll() const;
	~Depot();
};