
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <cstdlib>
#include <iostream>

using namespace std;

template<class T>
class LinkedList {

public:
	LinkedList() : _size(0), _front(nullptr) {}
	LinkedList(LinkedList& other) = delete;
	LinkedList(initializer_list<T> list) : _size(0), _front(nullptr) {

		// Optimize this:
		for (auto it = list.begin(); it != list.end(); ++it) {
			add(*it);
		}
	}

	~LinkedList() {
		if (_front != nullptr) {
			deleteNodes(_front);
		}

		_front = nullptr;
		_size = 0;
	}

	void add(T value) {

		if (_front == nullptr) {
			_front = new ListNode(value, nullptr);

		} else {
			ListNode* current = getNodeAtIndex(_front, _size - 1);
			current->_next = new ListNode(value, nullptr);
		}

		_size++;
	}

	T remove(unsigned int idx) {

		if (_front == nullptr || idx >= _size) {
			throw invalid_argument("idx >= size (or empty list)");
		}

		ListNode* current = _front;
		if (idx == 0) {
			T data = current->_data;
			_front = _front->_next;

			delete current;
			_size--;
			return data;
		}

		current = getNodeAtIndex(_front, idx - 1);
		ListNode* temp = current->_next;

		T data = temp->_data;
		current->_next = temp->_next;
		delete temp;
		return data;
	}

	void removeAll() {

		deleteNodes(_front);
		_front = nullptr;
		_size = 0;
	}

	int indexOf(const T& value, unsigned int idx) {

		if (idx >= _size) {
			throw invalid_argument("idx >= size");
		}

		// sanity check
		if (_front != nullptr) {
			ListNode* current = getNodeAtIndex(_front, idx);
			if (current != nullptr) {
				unsigned int i = 1;
				current = current->_next;
				while (current != nullptr) {
					if (current->_data == value) {
						return idx + i;
					}

					i++;
					current = current->_next;
				}
			}
		}

		return -1;
	}

	int indexOf(const T& value) {

		return indexOf(value, 0);
	}

	int lastIndexOf(const T& value) {

		int idx = indexOf(value);
		int prevIdx = idx;
		while (idx != -1) {
			prevIdx = idx;
			idx = indexOf(value, idx);
		}

		return prevIdx;
	}

	bool isEmpty() const {

		return (_front == nullptr && _size == 0);
	}

	unsigned int size() const {

		return _size;
	}

	T& get(unsigned int idx) {

		if (idx >= _size) {
			throw invalid_argument("idx >= size");
		}

		return getNodeAtIndex(_front, idx)->_data;
	}

	T set(unsigned int idx, T value) {

		T prev = get(idx);
		get(idx) = value;
		return prev;
	}

	T& operator[](unsigned int idx) {

		return get(idx);
	}

	friend ostream& operator<< (ostream& out, const LinkedList<T>& list) {

		out << "[";
		if (list._size != 0 && list._front != nullptr) {
			out << list._front->_data;
			ListNode* current = list._front->_next;
			while (current != nullptr) {
				out << ", " << current->_data;
				current = current->_next;
			}
		}

		return out << "]";
	}

private:
	struct ListNode {
		ListNode() : _data(), _next(nullptr) {}
		ListNode(T data, ListNode* next) : _data(data), _next(next) {}
		~ListNode() {}

		T _data;
		ListNode* _next;
		//ListNode* _prev;
	};

	unsigned int _size;
	ListNode* _front;
	//ListNode* _back;

	ListNode* getNodeAtIndex(ListNode* start, unsigned int idx) {

		unsigned int i = 0;
		ListNode* current = start;
		while (current != nullptr) {
			if (i == idx) {
				return current;
			}

			i++;
			current = current->_next;
		}

		return nullptr;
	}

	void deleteNodes(ListNode* current) {

		if (current != nullptr) {
			deleteNodes(current->_next);
			delete current;
		}
	}
};

#endif
