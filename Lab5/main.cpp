#include "Tensor.h"
#include <iostream>
#include <locale>
using namespace std;

int main() {
	setlocale(LC_ALL, "");

	cout << "Демонстрация работы класса Tensor (1D)\n\n";

	cout << "1. Конструкторы:\n";
	Tensor t1;
	Tensor t2(3);
	cout << "t1 = " << t1 << "\n";
	cout << "t2 = " << t2 << "\n";

	cout << "2. Заполнение через оператор []:\n";
	
	for (int i = 0; i < t2.getLength(); i++)
		t2[i] = (i + 1) * 1.5;

	cout << "t2 после заполнения: " << t2 << "\n\n";

	cout << "3. Арифметические операторы:\n";
	Tensor a(3); 
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	Tensor b(3);
	b[0] = 4;
	b[1] = 5;
	b[2] = 6;

	cout << "a = " << a << "\n";
	cout << "b = " << b << "\n";

	cout << "a + b = " << a + b << "\n";
	cout << "a - b = " << a - b << "\n";
	cout << "a * b = " << a * b << "\n";
	cout << "a / b = " << a / b << "\n";

	cout << "4. Составное присваивание: \n";
	Tensor c = a;
	c += b;
	cout << "c = a; c += b; => " << c << "\n\n";

	cout << "5. Сравнения: \n";
	cout << "a == a? " << (a == a ? "yes" : "no") << "\n";
	cout << "a == b? " << (a == b ? "yes" : "no") << "\n";
	cout << "a < b? " << (a < b ? "yes" : "no") << "\n";

	cout << "6. Инкремент и декремент: \n";
	cout << "a = " << a << "\n";
	cout << "++a = " << ++a << "\n";
	cout << "a++ = " << a++ << "\n";
	cout << "a = " << a << "\n\n";

	cout << "7. Оператор (): \n";
	cout << "a(0) = " << a(0) << ", a(1) = " << a(1) << "\n\n";

	cout << "8. Преобразование типов: \n";
	cout << "Среднее элементов a: " << static_cast<double>(a) << "\n\n";

	cout << "9. Умножение тензора на число: \n";
	cout << "a * 2.0 = " << a * 2.0 << "\n";
	cout << "10.0 * a = " << 10.0 * a << "\n\n";

	cout << "10. Свёртка тензоров: \n";
	Tensor input(5);
	input[0] = 1;
	input[1] = 2;
	input[2] = 3;
	input[3] = 4;
	input[4] = 5;

	Tensor core(3);
	core[0] = 1;
	core[1] = 0;
	core[2] = -1;

	cout << "Входной тензор: " << input << "\n";
	cout << "Ядро: " << core << "\n";
	Tensor result = input.convolve(core);
	cout << "Результат свёртки: " << result << "\n";
	cout << "**Ответ должен быть: [-2, -2, -2]**\n\n";

	cout << "11. Демонстрация ввода (оператор >>): \n";
	Tensor t_input(3);
	cout << "Введите 3 числа: ";
	cin >> t_input;
	cout << "Вывод: " << t_input << "\n\n";

	cout << "Завершение демонстрации\n";

	return 0;
}