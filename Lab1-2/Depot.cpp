#include "Depot.h"

using namespace std;

Depot* Depot::singleton = nullptr;

Depot::Depot() {
	cout << "Автопарк создан" << endl;
}

Depot* Depot::getSingleton() {
	if (singleton == nullptr)
		singleton = new Depot();

	return singleton;
}

void Depot::addBus(Bus* b) {
	if (b != nullptr) {
		bus.push_back(b);
		cout << "Автобус добавлен в автопарк" << endl;
	}
}

void Depot::printAll() const {
	cout << "\nСписок автобусов в автопарке: " << endl;

	for (const auto* b : bus) {
		b->print();
	}
}

Depot::~Depot() {
	cout << "Автопарк закрыт" << endl;
	singleton = nullptr;
}