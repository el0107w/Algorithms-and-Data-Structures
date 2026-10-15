#include <iostream>
#include <locale>
#include "IntVector.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "");

	cout << "Демонстрация работы IntVector\n\n";

	cout << "1. Конструктор по умолчанию:\n";
	IntVector v1;
	v1.print();
	cout << "Размер: " << v1.getSize() << "\n\n";

	cout << "2. Конструктор размера:\n";
	IntVector v2(5);
	v2.print();
	cout << "\n";

	cout << "3. Добавление элементов:\n";
	IntVector v3;

	for (int i = 1; i <= 15; i++)
		v3.pushBack(i);

	v3.print();
	cout << "Размер: " << v3.getSize() << ", Ёмкость: " << v3.getCapacity() << "\n\n";

	cout << "4. Доступ по индексу:\n";
	cout << "v3[0] = " << v3[0] << ", v3[5] = " << v3[5] << "\n\n";

	cout << "5. Конструктор копирования:\n";
	IntVector v5 = v3;
	v5.print();
	cout << "\n";

	cout << "6. Удаление последнего элемента:\n";
	v3.popBack();
	v3.print();
	cout << "Размер после popBack: " << v3.getSize() << "\n\n";

	cout << "7. Проверка глубокого копирования:\n";
	v3[0] = 999;
	cout << "v3[0] = 999\n";
	cout << "v3: ";
	v3.print();
	cout << "v5: ";
	v5.print();
	
	cout << "v5[0] не изменился - глубокое копирование!\n\n";

	cout << "8. Реализация итераторов (begin, end) для поддержки range-based for:\n";
	cout << "v2 ";

	for (int x : v2)
		cout << x << " ";
	cout << "\n\n";

	cout << "9. Вставка методом insert:\n";
	IntVector v6(3);
	cout << "До вставки: ";
	v6.print();
	v6.insert(v6.begin() + 1, 17);
	cout << "После вставки: ";
	v6.print();
	cout << "\n\n";

	cout << "10. Резервирование памяти методом reserve:\n";
	IntVector v7(5);
	cout << "Начальная ёмкость: " << v7.getCapacity() << "\n";
	v7.reserve(10);
	cout << "Ёмкость после резервирования: " << v7.getCapacity() << "\n\n";

	cout << "11. Уменьшение ёмкости до размера методом shrinkToFit():\n";
	v7.shrinkToFit();
	cout << "Ёмкость после уменьшения: " << v7.getCapacity() << "\n";

	return 0;
}