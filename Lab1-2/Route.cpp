#include "Route.h"

using namespace std;

Route::Route(int num, string start, string end) : routeNum(num), startPoint(start), endPoint(end) {
	cout << "Создан маршрут №" << routeNum << endl;
}


void Route::print() const {
	cout << "Маршрут №" << routeNum << " (" << startPoint << " - " << endPoint << ")";
}

Route::~Route() {
	cout << "Удалён маршрут №" << routeNum << endl;
}