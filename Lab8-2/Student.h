#pragma once
#include <string>
using namespace std;

struct Student {
    string name;
    int course;

    Student() : name(""), course(0) {}
    Student(const string& n, int c) : name(n), course(c) {}
};