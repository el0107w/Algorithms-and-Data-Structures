#pragma once
#include <iostream>
#include <string>

class Complex {
private:
	double re;
	double im;
	static int count;

public:
	Complex();
	Complex(double r, double i);
	Complex(const Complex& other);

	~Complex();

	double getRe() const;
	double getIm() const;

	void setRe(double r);
	void setIm(double i);

	double getAbs() const;
	double getArg() const;

	void printInf() const;
	static int getCount();

	friend std::ostream& operator<<(std::ostream& os, const Complex& c);

	void inFile(const std::string& file) const;
	void outFile(const std::string& file);
};