#pragma once
#include <string>
#include <iostream>

using namespace std;

class Route {
private: 
	int routeNum;
	string startPoint;
	string endPoint;
public:
	Route(int num, string start, string end);
	void print() const;
	~Route();
};