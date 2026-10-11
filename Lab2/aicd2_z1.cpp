#include <iostream>
#include <vector>
#include <locale>
#include <algorithm>
#include <cmath>
using namespace std;

bool isPerfSqr(int x) {
	if (x < 0)
		return false;
	int r = (int)sqrt(x);
	return r * r == x;
}

int main() {
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите целое число n - количество чисел, из которых состоит вектор: ";
	cin >> n;
	vector<int> v(n);

	cout << "Заполните вектор v целыми числами: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	v.erase(remove_if(v.begin(), v.end(), isPerfSqr), v.end());

	cout << "Вектор, после удаления всех элементов, которые являются полными квадратами: " << endl;
	for (int x : v)
		cout << x << " ";

	int sum = 0;
	for (int x : v) {
		sum += x;
	}
	cout << "\nСумма элементов, оставшихся в векторе: " << sum << endl;

	return 0;
}