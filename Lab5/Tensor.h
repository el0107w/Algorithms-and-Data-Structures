#pragma once
#include <iostream>

class Tensor {
private:
	double* data;
	int* dimension;
	int rank;
	int length;

public:
	Tensor();
	Tensor(int length);
	Tensor(const Tensor& other);
	Tensor(Tensor&& other) noexcept;

	~Tensor();

	Tensor& operator=(const Tensor& other);
	Tensor& operator=(Tensor&& other) noexcept;

	int getLength() const;
	int getRank() const;
	int getNumElement() const;

	double& operator[](int index);
	const double& operator[](int index) const;

	void print() const;

	friend std::istream& operator>>(std::istream& is, Tensor& t);
	friend std::ostream& operator<<(std::ostream& os, const Tensor& t);

	bool operator==(const Tensor& other) const;
	bool operator!=(const Tensor& other) const;

	Tensor operator+(const Tensor& other) const;
	Tensor operator-(const Tensor& other) const;
	Tensor operator*(const Tensor& other) const;
	Tensor operator/(const Tensor& other) const;

	Tensor& operator+=(const Tensor& other);
	Tensor& operator-=(const Tensor& other);
	Tensor& operator*=(const Tensor& other);
	Tensor& operator/=(const Tensor& other);

	bool operator<(const Tensor& other) const;
	bool operator>(const Tensor& other) const;
	bool operator<=(const Tensor& other) const;
	bool operator>=(const Tensor& other) const;

	Tensor& operator++();
	Tensor operator++(int);
	Tensor& operator--();
	Tensor operator--(int);

	double& operator()(int index);
	const double& operator()(int index) const;

	explicit operator double() const;

	friend Tensor operator*(double vector, const Tensor& t);
	friend Tensor operator*(const Tensor& t, double scalar);

	Tensor convolve(const Tensor& core) const;
};