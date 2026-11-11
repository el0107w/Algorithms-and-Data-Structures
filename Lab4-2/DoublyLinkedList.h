#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
	struct DNode {
		T data;
		DNode* prev;
		DNode* next;
		DNode(const T& value) : data(value), prev(nullptr), next(nullptr) {}
	};

	DNode* head;
	DNode* tail;
	int count;

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
	~DoublyLinkedList() { clear(); }

	void push_back(const T& value) {
		DNode* newDNode = new DNode(value);
		if (!tail)
			head = tail = newDNode;
		else {
			tail->next = newDNode;
			newDNode->prev = tail;
			tail = newDNode;
		}
		count++;
	}

	void push_front(const T& value) {
		DNode* newDNode = new DNode(value);
		if (!head)
			head = tail = newDNode;
		else {
			newDNode->next = head;
			head->prev = newDNode;
			head = newDNode;
		}
		count++;
	}

	void pop_front() {
		if (!head)
			throw underflow_error("List is empty");
		DNode* temp = head;
		head = head->next;
		if (head)
			head->prev = nullptr;
		else
			tail = nullptr;
		delete temp;
		count--;
	}

	void print() const {
		DNode* curr = head;
		cout << "[";
		while (curr) {
			cout << curr->data;
			if (curr->next)
				cout << ", ";
			curr = curr->next;
		}
		cout << "]" << endl;
	}

	int size() const { return count; }

	// Обмен соседних элементов
	void swapEls() {
		if (!head || !head->next)
			return;
		DNode* curr = head;
		head = head->next;

		while (curr && curr->next) {
			DNode* first = curr;
			DNode* second = curr->next;
			DNode* nextEl = second->next;

			second->prev = first->prev;
			if (first->prev)
				first->prev->next = second;

			second->next = first;
			first->prev = second;
			first->next = nextEl;

			if (nextEl)
				nextEl->prev = first;
			else
				tail = first;

			curr = nextEl;
		}
	}

	void clear() {
		while (head) {
			DNode* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		count = 0;
	}
};