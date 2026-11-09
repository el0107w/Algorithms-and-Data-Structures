#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <ctime>
#include "RingBuffer.h"

using namespace std;
using namespace chrono;

// Функция для замера времени выполнения
template <typename Func>
long long leadTime(Func f) {
	auto start = high_resolution_clock::now();
	f();
	auto end = high_resolution_clock::now();

	return duration_cast<microseconds>(end - start).count();
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(0));
	cout << "Демонстрация работы RingBuffer" << endl;

	RingBuffer<int> rb(5);
	cout << "Заполнение буфера случайными числами и перезапись:" << endl;

	for (int i = 0; i < 10; i++) {
		int randNum = rand() % 201 - 100;
		rb.push(randNum);

		cout << "Добавлено: " << randNum << " | Буфер: [";

		for (size_t j = 0; j < rb.size(); j++) {
			cout << rb[j];
			if (j < rb.size() - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}

	const int N = 10000;

		// Тест 1: RingBuffer
	RingBuffer<int> rBuff(N);
	long long timeRPush = leadTime([&]() {
		for (int i = 0; i < N; i++)
			rBuff.push(i);
		});
	long long timeRPop = leadTime([&]() {
		for (int i = 0; i < N; i++)
			rBuff.pop();
		});

		// Тест 2: std::queue (аналог из STL)
	queue<int> stdQue;
	long long timeQPush = leadTime([&]() {
		for (int i = 0; i < N; i++)
			stdQue.push(i);
		});
	long long timeQPop = leadTime([&]() {
		for (int i = 0; i < N; i++)
			stdQue.pop();
		});

		// Тест 3: std::vector
	const int V = 10000;
	vector<int> v;
	long long timeVPush = leadTime([&]() {
		for (int i = 0; i < V; i++)
			v.push_back(i);
		});
	long long timeVErase = leadTime([&]() {
		for (int i = 0; i < V; i++)
			v.erase(v.begin());
		});

	cout << "Операция: " << N << " итераций (для вектора " << V << ")" << endl;
	cout << "\nКонтейнер\t\tpush (мкс)\tpop/erase (мкс)" << endl;
	cout << "\nRingBuffer<T>\t\t" << timeRPush << "\t\t" << timeRPop << endl;
	cout << "\nstd::queue<T>\t\t" << timeQPush << "\t\t" << timeQPop << endl;
	cout << "\nstd::vector<T>\t\t" << timeVPush << "\t\t" << timeVErase << " (erase)" << endl;
	cout << "\nВывод: RingBuffer и std::queue выполняют операции за O(1)." << endl;
	cout << "std::vector при удалении из начала тратит O(N) на сдвиг элементов, поэтому на 10 000 элементах он бы работал в разы дольше." << endl;

	return 0;
}