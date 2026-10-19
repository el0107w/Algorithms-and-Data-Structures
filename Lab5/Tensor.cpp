#include "Tensor.h"
#include <stdexcept>

Tensor::Tensor() : rank(1), length(0) {
	data = nullptr;
	dimension = new int[1];
	dimension[0] = 0;

}

Tensor::Tensor(int length) : rank(1), length(length) {
	if (length < 0)
		throw std::invalid_argument("Длина не может быть отрицательной");
	data = new double[length]();
	dimension = new int[1];
	dimension[0] = length;
}

Tensor::Tensor(const Tensor& other) : rank(other.rank), length(other.length) {
	if (other.length == 0) {
		data = nullptr;
		dimension = new int[1];
		dimension[0] = 0;
		return;
	}
	data = new double[length];

	for (int i = 0; i < length; i++)
		data[i] = other.data[i];

	dimension = new int[1];
	dimension[0] = other.dimension[0];
}

Tensor::Tensor(Tensor&& other) noexcept : data(other.data), dimension(other.dimension), rank(other.rank), length(other.length) {
	other.data = nullptr;
	other.dimension = nullptr;
	other.rank = 0;
	other.length = 0;
}

Tensor::~Tensor() {
	delete[] data;
	delete[] dimension;
}

Tensor& Tensor::operator=(const Tensor& other) {
	if (this != &other) {
		delete[] data;
		delete[] dimension;

		rank = other.rank;
		length = other.length;

		if (other.length == 0) {
			data = nullptr;
			dimension = new int[1];
			dimension[0] = 0;
		}
		else {
			data = new double[length];

			for (int i = 0; i < length; i++)
				data[i] = other.data[i];

			dimension = new int[1];
			dimension[0] = other.dimension[0];
		}
	}

	return *this;
}

Tensor& Tensor::operator=(Tensor&& other) noexcept {
	if(this != &other) {
		delete[] data;
		delete[] dimension;

		data = other.data;
		dimension = other.dimension;
		rank = other.rank;
		length = other.length;

		other.data = nullptr;
		other.dimension = nullptr;
		other.rank = 0;
		other.length = 0;
	}
	return *this;
}

int Tensor::getLength() const { return length; }
int Tensor::getRank() const { return rank; }
int Tensor::getNumElement() const { return length; }

double& Tensor::operator[](int index) {
	if (index < 0 || index >= length)
		throw std::out_of_range("Индекс вне диапазона");
	
	return data[index];
}

const double& Tensor::operator[](int index) const {
	if (index < 0 || index >= length)
		throw std::out_of_range("Индекс вне диапазона");

	return data[index];
}

void Tensor::print() const {
	std::cout << "[";

	for (int i = 0; i < length; i++) {
		std::cout << data[i];
		if (i < length - 1)
			std::cout << ", ";
	}
	std::cout << "]";
}

std::istream& operator>>(std::istream& is, Tensor& t) {

	for (int i = 0; i < t.length; i++)
		is >> t.data[i];

	return is;
}

std::ostream& operator<<(std::ostream& os, const Tensor& t) {
	os << "[";

	for (int i = 0; i < t.length; i++) {
		os << t.data[i];
		if (i < t.length - 1)
			os << ", ";
	}
	os << "]";
	
	return os;
}

bool Tensor::operator==(const Tensor& other) const {
	if (length != other.length)
		return false;

	for (int i = 0; i < length; i++) {
		if (data[i] != other.data[i])
			return false;
	}

	return true;
}

bool Tensor::operator!=(const Tensor& other) const {
	return !(*this == other);
}

Tensor Tensor::operator+(const Tensor& other) const {
	if (length != other.length)
		throw std::invalid_argument("Размеры тензоров должны совпадать");

	Tensor result(length);

	for (int i = 0; i < length; i++)
		result.data[i] = data[i] + other.data[i];

	return result;
}

Tensor Tensor::operator-(const Tensor& other) const {
	if (length != other.length)
		throw std::invalid_argument("Размеры тензоров должны совпадать");

	Tensor result(length);

	for (int i = 0; i < length; i++)
		result.data[i] = data[i] - other.data[i];

	return result;
}

Tensor Tensor::operator*(const Tensor& other) const {
	if (length != other.length)
		throw std::invalid_argument("Размеры тензоров должны совпадать");

	Tensor result(length);

	for (int i = 0; i < length; i++)
		result.data[i] = data[i] * other.data[i];

	return result;
}

Tensor Tensor::operator/(const Tensor& other) const {
	if(length!=other.length)
		throw std::invalid_argument("Размеры тензоров должны совпадать");

	Tensor result(length);

	for (int i = 0; i < length; i++) {
		if (other.data[i] == 0)
			throw std::runtime_error("Деление на ноль");

		result.data[i] = data[i] / other.data[i];
	}
	return result;
}

Tensor& Tensor::operator+=(const Tensor& other) {
	*this = *this + other;

	return *this;
}

Tensor& Tensor::operator-=(const Tensor& other) {
	*this = *this - other;

	return *this;
}

Tensor& Tensor::operator*=(const Tensor& other) {
	*this = *this * other;

	return *this;
}

Tensor& Tensor::operator/=(const Tensor& other) {
	*this = *this / other;

	return *this;
}

bool Tensor::operator<(const Tensor& other) const {
	if (length != other.length)
		throw std::invalid_argument("Размеры тензоров должны совпадать");

	for (int i = 0; i < length; i++) {
		if (data[i] >= other.data[i])
			return false;
	}
	return true;
}

bool Tensor::operator>(const Tensor& other) const {
	if (length != other.length)
		throw std::invalid_argument("Размеры тензоров должны совпадать");

	for (int i = 0; i < length; i++) {
		if (data[i] <= other.data[i])
			return false;
	}
	return true;
}

bool Tensor::operator<= (const Tensor& other) const {
	return(*this < other) || (*this == other);
}

bool Tensor::operator>=(const Tensor& other) const {
	return(*this > other) || (*this == other);
}

Tensor& Tensor::operator++() {

	for (int i = 0; i < length; i++) {
		data[i] += 1.0;
	}
	return *this;
}

Tensor Tensor::operator++(int) {
	Tensor temp = *this;

	for (int i = 0; i < length; i++) {
		data[i] += 1.0;
	}
	return temp;
}

Tensor& Tensor::operator--() {

	for (int i = 0; i < length; i++) {
		data[i] -= 1.0;
	}
	return *this;
}

Tensor Tensor::operator--(int) {
	Tensor temp = *this;

	for (int i = 0; i < length; i++) {
		data[i] -= 1.0;
	}
	return temp;
}

double& Tensor::operator()(int index) {
	if (index < 0 || index >= length)
		throw std::out_of_range("Индекс вне диапазона");

	return data[index];
}

const double& Tensor::operator()(int index) const {
	if (index < 0 || index >= length)
		throw std::out_of_range("Индекс вне диапазона");

	return data[index];
}

Tensor::operator double() const {
	if (length == 0)
		return 0.0;
	double sum = 0;

	for (int i = 0; i < length; i++)
		sum += data[i];

	return sum / length;
}

Tensor operator*(double vector, const Tensor& t) {
	Tensor result(t.length);

	for (int i = 0; i < t.length; i++)
		result.data[i] = t.data[i] * vector;

	return result;
}

Tensor operator*(const Tensor& t, double vector) {
	return vector * t;
}

Tensor Tensor::convolve(const Tensor& core) const {
	if(core.length>length)
		throw std::invalid_argument("Ядро больше тензора");

	if(core.length ==0)
		throw std::invalid_argument("Ядро пустое");

	int outLength = length - core.length + 1;
	Tensor result(outLength);

	for (int i = 0; i < outLength; i++) {
		double sum = 0;
		for (int j = 0; j < core.length; j++)
			sum += data[i + j] * core.data[j];

		result.data[i] = sum;
	}
	return result;
}
