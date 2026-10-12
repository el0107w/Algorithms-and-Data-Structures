#include <iostream>
#include <locale>
#include <cmath>
#include "Complex.h"

int main() {
	setlocale(LC_ALL, "");

	std::cout << "Демонстрация работы с классом Complex\n" << std::endl;

	std::cout << "Создание объекта 1 (конструктор по умолчанию)" << std::endl;
	Complex complex1;
	complex1.printInf();
	std::cout << std::endl;

	std::cout << "Изменение данных через сеттеры" << std::endl;
	complex1.setRe(7.0);
	complex1.setIm(17.0);
	complex1.printInf();
	std::cout << std::endl;

	std::cout << "Создание объекта 2 (параметризованный конструктор)" << std::endl;
	Complex complex2(3.0, 13.0);
	complex2.printInf();
	std::cout << std::endl;

	std::cout << "Использование геттеров для объекта 2" << std::endl;
	std::cout << "Действительная часть: " << complex2.getRe() << std::endl;
	std::cout << "Мнимая часть: " << complex2.getIm() << std::endl;

	std::cout << "Создание объекта 3 (конструктор копирования)" << std::endl;
	Complex complex3 = complex2;
	complex3.printInf();
	std::cout << std::endl;

	std::cout << "Проверка корректности данных в сеттерах" << std::endl;
	double nan = std::nan("");
	complex1.setRe(nan);
	complex1.setIm(nan);
	complex1.printInf();
	std::cout << std::endl;

	std::cout << "Перегрузка оператора <<" << std::endl;
	Complex c_demo(9.0, -19.0);
	std::cout << c_demo << std::endl;
	std::cout << std::endl;

	std::cout << "Массив объектов класса и работа с ним" << std::endl;
	Complex arr[3] = { Complex(11.1, 21.2), Complex(13.3, 23.4), Complex(17.5, 27.6) };

	for (int i = 0; i < 3; i++) {
		std::cout << "arr[" << i << "]: ";
		arr[i].printInf();
		std::cout << std::endl;
	}

	std::cout << "Количество созданных объектов: " << Complex::getCount() << std::endl;
	std::cout << std::endl;

	std::cout << "Сохранение информации об объекте и загрузка данных" << std::endl;
	Complex c_save(81.2, 66.6);
	std::cout << "Исходные числа: " << c_save << std::endl;
	c_save.inFile("complex.txt");
	Complex c_load;
	c_load.outFile("complex.txt");
	std::cout << "Загруженные числа " << c_load << std::endl;

	std::cout << "Завершение программы" << std::endl;

	return 0;
}