#pragma once
#include <iostream>
#include <stdexcept>
#include <vector> 

using namespace std;

template <typename T>
class SinglyLinkedList {
private:
	struct SNode {
		T data;
		SNode* next;
		SNode(const T& value) : data(value), next(nullptr) {}
	};

	SNode* head;
	SNode* tail;
	int count;

public:
	SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
	~SinglyLinkedList() { clear(); }

	void push_front(const T& value) {
		SNode* newSNode = new SNode(value);
		newSNode->next = head;
		head = newSNode;
		if (tail == nullptr)
			tail = newSNode;
		count++;
	}

	void pop_front() {
		if (!head)
			throw underflow_error("List is empty");

		SNode* temp = head;
		head = head->next;
		delete temp;
		count--;

		if (head == nullptr)
			tail = nullptr;
	}

	int size() const { return count; }
	bool empty() const { return head == nullptr; }

	void print() const {
		SNode* curr = head;
		cout << "[";
		while (curr) {
			cout << curr->data;
			if (curr->next)
				cout << ", ";
			curr = curr->next;
		}
		cout << "]" << endl;
	}

	bool checkMirror() const {
		if (!head || !head->next)
			return true;

		// 1. Копируем данные в вектор
		vector<T> elements;
		SNode* curr = head;
		while (curr) {
			elements.push_back(curr->data);
			curr = curr->next;
		}

		// 2. Проверяем с двух концов (как в массиве)
		int left = 0;
		int right = elements.size() - 1;
		while (left < right) {
			if (elements[left] != elements[right]) {
				return false;
			}
			left++;
			right--;
		}
		return true;
	}

	void clear() {
		while (head) {
			SNode* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		count = 0;
	}
};