#define _USE_MATH_DEFINES
#include "Complex.h"
#include <iostream>
#include <cmath>
#include <fstream>

int Complex::count = 0;

Complex::Complex()
	:re(0.0),
	im(0.0) {
	count++;
	std::cout << "Вызван конструктор по умолчанию для объекта: " << count << std::endl;
}

Complex::Complex(double r, double i)
	:re(r), im(i) {
	count++;
	std::cout << "Вызван параметризованный конструктор для объекта: " << re;
	if (im >= 0)
		std::cout << " + " << im << "i" << std::endl;
	else
		std::cout << " - " << -im << "i" << std::endl;
}

Complex::Complex(const Complex& other)
	:re(other.re), im(other.im) {
	count++;
	std::cout << "Вызван конструктор копирования для объекта: " << re;
	if (im >= 0)
		std::cout << " + " << im << "i" << std::endl;
	else
		std::cout << " - " << -im << "i" << std::endl;
}

Complex::~Complex() {
	count--;
	std::cout << "Вызван деструктор для объекта " << re;
	if (im >= 0)
		std::cout << " + " << im << "i" << std::endl;
	else
		std::cout << " - " << -im << "i" << std::endl;
}

double Complex::getRe() const {
	return re;
}
double Complex::getIm() const {
	return im;
}

void Complex::setRe(double r) {
	if (!std::isnan(r))
		re = r;
	else
		std::cout << "Ошибка: re должно быть числом!" << std::endl;
}

void Complex::setIm(double i) {
	if (!std::isnan(i))
		im = i;
	else
		std::cout << "Ошибка: im должно быть числом!" << std::endl;
}
double Complex::getAbs() const {
	return std::sqrt(re * re + im * im);
}

double Complex::getArg() const {
	double rad = std::atan2(im, re);
	return rad * 180.0 / M_PI;
}

void Complex::printInf() const {
	std::cout << "Действительная часть: " << re << std::endl;
	std::cout << "Мнимая часть: " << im << std::endl;
	std::cout << "Модуль числа: " << getAbs() << std::endl;
	std::cout << "Аргумент числа в градусах: " << getArg() << std::endl;
}

int Complex::getCount() {
	return count;
}
std::ostream& operator<<(std::ostream& os, const Complex& c) {
	os << c.re;
	if (c.im >= 0)
		os << " + " << c.im << "i";
	else
		os << " - " << -c.im << "i";
	return os;
}
	
void Complex::inFile(const std::string& file) const {
	std::ofstream fOut(file);
	if (!fOut.is_open()) {
		std::cerr << "Не удалось открыть файл " << file << std::endl;
		return;
	}
	fOut << re << " " << im;
	fOut.close();
	std::cout << "Числа сохранены в " << file << std::endl;
}
void Complex::outFile(const std::string& file) {
	std::ifstream fIn(file);
	if (!fIn.is_open()) {
		std::cerr << "Не удалось открыть файл " << file << std::endl;
		return;
	}
	fIn >> re >> im;
	fIn.close();
	std::cout << "Числа прочитаны из " << file << std::endl;
}