#include <iostream>
#include "Route.h"
#include "Bus.h"
#include "Depot.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "");

	cout << "1. Создание маршрутов" << endl;

	Route route1(20, "Дом", "ТЦ Космос");
	Route route2(13, "СКФУ", "Автостанция №1");

	cout << "\n2. Создание автобусов" << endl;

	Bus bus1("Toyota HiAce", "S812KA");
	Bus bus2("Mercedes-Benz Sprinter", "K666AI");

	cout << "\n3. Привязка маршрутов к автобусам (агрегация)" << endl;

	bus1.setRoute(&route1);
	bus2.setRoute(&route2);

	cout << "\n4. Статическое поле" << endl;

	cout << "Создано автобусов: " << Bus::getTotalBus() << endl;
	
	cout << "\n5. Паттерн 'Одиночка' (Автопарк)" << endl;

	Depot* depot1 = Depot::getSingleton();
	Depot* depot2 = Depot::getSingleton();

	if (depot1 == depot2) {
		cout << "depot1 и depot2 указывают на один объект" << endl;
	}

	cout << "\n6. Добавление автобусов в автопарк (агрегация)" << endl;

	depot1->addBus(&bus1);
	depot1->addBus(&bus2);
	depot1->printAll();

	cout << "\n7. Уничтожение автопарка" << endl;

	delete depot1;

	cout << "\n8. Проверка агрегации" << endl;

	cout << "Автопарк уничтожен. Автобусы в наличии:" << endl;
	bus1.print();
	bus2.print();

	bus1.removeRoute();
	cout << "Отвязка маршрута:" << endl;
	bus1.print();

	cout << "\n9. Конец программы" << endl;

	return 0;
}
