#include "Bus.h"

using namespace std;

int Bus::totalBus = 0;

Bus::Bus(const string& mdl, const string& regNum) : model(mdl), registrNum(regNum), currentRoute(nullptr) {
	totalBus++;
	cout << "Создан автобус: " << model << endl;
}

Bus::~Bus() {
	totalBus--;
	cout << "Удалён автобус: " << model << endl;
}

void Bus::setRoute(Route* r) {
	currentRoute = r;
}

void Bus::removeRoute() {
	currentRoute = nullptr;
}

int Bus::getTotalBus() {
	return totalBus;
}

void Bus::print() const {
	cout << "Автобус: " << model << " [" << registrNum << "] ";
	if (currentRoute != nullptr) {
		currentRoute->print();
		cout << endl;
	}
	else
		cout << "Без маршрута" << endl;
}