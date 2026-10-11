#include <iostream>
#include <locale>
#include <vector>
#include <cmath>
using namespace std;

vector<int> input() {
	int n;
	cout << "Введите количество элементов вектора: ";
	cin >> n;
    vector<int> v(n);

	cout << "Заполните вектор v целыми числами: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	return v;
}

bool findThree(int x) {
	x = abs(x);
	while (x > 0) {
		if (x % 10 == 3)
			return true;
		x = x / 10;
	}
	return false;
}

bool isPrimeNum(int x) {
	if (x < 2)
		return false;
	for (int i = 2; i  <= (int)sqrt(x); i++) {
		if (x % i == 0)
			return false;
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "");

	vector<int> v = input();
	int count = 0;
	int mnSum = 0;
	bool flag = true;
	
	for (int i = 0; i < (int)v.size() - 2; i++) {
		if (!findThree(v[i]) || !findThree(v[i + 1]) || !findThree(v[i + 2]))
			continue;

		int sum = v[i] + v[i + 1] + v[i + 2];
		if (!isPrimeNum(sum))
			continue;
		if (flag) {
			mnSum = sum;
			flag = false;
		}
		else if (sum < mnSum)
			mnSum = sum;
		count++;
	}

	cout << "Количество троек элементов последовательности, в которых каждое число содержит цифру 3: " << count << endl;
	if (count > 0)
		cout << "Минимальная сумма элементов таких троек: " << mnSum << endl;
	else
		cout << "Троек, удовлетворяющих условиям нет" << endl;

	return 0;
}