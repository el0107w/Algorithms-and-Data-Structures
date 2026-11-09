#pragma once
#include <iostream>
#include <string>
#include "Route.h"

using namespace std;

class Bus {
private:
	string model;
	string registrNum;
	Route* currentRoute;					// Агрегация (указатель на маршрут)
	static int totalBus;					// Статический счетчик
public:
	Bus(const string& mdl, const string& regNum);
	~Bus();
	void setRoute(Route* r);
	void removeRoute();
	static int getTotalBus();
	void print() const; 
};