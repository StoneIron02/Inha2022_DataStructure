#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* prev;
	node* next;
};

class DLinkedList {
public:
	DLinkedList() {
		head = tail = new node;
		head->next = tail;
		tail->prev = head;
		size = 0;
	}
	bool empty() {
		return (size == 0);
	}
	void append(int data) {
		node* newNode = new node;
		newNode->data = data;

		node* curNode = tail->prev;
		newNode->prev = curNode;
		newNode->next = tail;
		curNode->next = newNode;
		tail->prev = newNode;
		size++;
		print();
	}
	int remove(int index) {
		if (empty() || index < 0 || index >= size) {
			return -1;
		}
		else {
			node* curNode = head->next;
			for (int i = 0; i < index; i++) {
				curNode = curNode->next;
			}
			node* preNode = curNode->prev;
			node* nextNode = curNode->next;

			preNode->next = nextNode;
			nextNode->prev = preNode;
			int data = curNode->data;
			delete curNode;
			size--;
			return data;
		}
	}
	void print() {
		if (empty()) {
			cout << "empty\n";
		}
		else {
			node* curNode = head->next;
			while (curNode != tail) {
				cout << curNode->data << " ";
				curNode = curNode->next;
			}
			cout << "\n";
		}
	}
	void print_reverse() {
		if (empty()) {
			cout << "empty\n";
		}
		else {
			node* curNode = tail->prev;
			while (curNode != head) {
				cout << curNode->data << " ";
				curNode = curNode->prev;
			}
			cout << "\n";
		}
	}
	void max() {
		if (empty()) {
			cout << "empty\n";
		}
		else {
			node* curNode = head->next;
			int max = curNode->data;
			while (curNode != tail) {
				(curNode->data > max) ? max = curNode->data : max = max;
				curNode = curNode->next;
			}
			cout << max << "\n";
		}
	}
private:
	node* head;
	node* tail;
	int size;
};

int main() {
	int m;
	cin >> m;

	DLinkedList l = DLinkedList();
	for (int i = 0; i < m; i++) {
		string command;
		cin >> command;
		if (command == "Append") {
			int x;
			cin >> x;
			l.append(x);
		}
		else if (command == "Delete") {
			int i;
			cin >> i;
			cout << l.remove(i) << "\n";
		}
		else if (command == "Print") {
			l.print();
		}
		else if (command == "Print_reverse") {
			l.print_reverse();
		}
		else if (command == "Max") {
			l.max();
		}
	}
}