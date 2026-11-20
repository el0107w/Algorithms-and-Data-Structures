#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Student.h"

using namespace std;

class HashTable {
private:
    struct Node {
        int key;
        Student value;
        Node* next;

        Node(int k, const Student& v) : key(k), value(v), next(nullptr) {}
    };

    vector<Node*> table;
    int size;
    int count;

    // Хеш-функция (остаток от деления)
    int hashFunc(int key) const {
        return abs(key) % size;
    }

public:
    HashTable(int s) : size(s), count(0) {
        table.resize(size, nullptr);
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    // Вставка (метод цепочек)
    void insert(int key, const Student& value) {
        int index = hashFunc(key);
        Node* current = table[index];

        // Проверка, есть ли уже такой ключ
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // Обновление значения
                return;
            }
            current = current->next;
        }

        // Если ключа нет, добавляем в начало списка (цепи)
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        count++;
    }

    // Поиск
    Student* find(int key) {
        int index = hashFunc(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return &current->value; // Возвращаем указатель на данные
            }
            current = current->next;
        }
        return nullptr; // Не найдено
    }
};