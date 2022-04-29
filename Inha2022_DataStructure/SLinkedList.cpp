#include <iostream>
#include <string>
using namespace std;

typedef int type;
struct node {
	type data;
	node* next;
};

class SLinkedList {
public:
	SLinkedList() {
		head = tail = NULL;
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	void append(type data) {
		node* newNode = new node();
		newNode->data = data;
		newNode->next = NULL;
		if (empty()) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		n++;
	}
	void insert(int index, type data) {
		if (index < 0 || index > n) {
			// OutOfIndex
			return;
		}
		else if (index == n) {
			append(data);
		}
		else if (index == 0) {
			node* newNode = new node();
			newNode->data = data;
			newNode->next = head;
			head = newNode;
			n++;
		}
		else {
			node* newNode = new node();
			newNode->data = data;

			node* curNode = head;
			for (int i = 1; i < index; i++) {
				curNode = curNode->next;
			}
			newNode->next = curNode->next;
			curNode->next = newNode;
			n++;
		}
	}
	void remove(int index) {
		if (empty()) {
			// ListEmpty
			return;
		}
		if (index < 0 || index >= n) {
			// OutOfIndex
			return;
		}
		node* curNode = head;
		if (index == 0) {
			if (n == 1) {
				head = tail = NULL;
			}
			else {
				head = head->next;
			}
		}
		else {
			node* prevNode = head;
			for (int i = 0; i < index; i++) {
				prevNode = curNode;
				curNode = curNode->next;
			}
			prevNode->next = curNode->next;
			if (curNode == tail) {
				tail = prevNode;
			}
		}
		delete curNode;
		n--;
	}
	void print() {
		node* curNode = head;
		while (curNode != NULL) {
			cout << curNode->data << " ";
			curNode = curNode->next;
		}
		cout << endl;
	}
private:
	node* head;
	node* tail;
	int n;
};

int main() {
	SLinkedList list = SLinkedList();
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << list.size() << endl;
		}
		else if (command == "empty") {
			cout << list.empty() << endl;
		}
		else if (command == "append") {
			int x;
			cin >> x;
			list.append(x);
		}
		else if (command == "insert") {
			int x, y;
			cin >> x >> y;
			list.insert(x, y);
		}
		else if (command == "remove") {
			int x;
			cin >> x;
			list.remove(x);
		}
		else if (command == "print") {
			list.print();
		}
	}
}