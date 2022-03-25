#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* next;
};

class LinkedList {
public:
	LinkedList() {
		head = tail = NULL;
		size = 0;
	}
	bool empty() {
		return (size == 0);
	}
	void append(int data) {
		node* newNode = new node;
		newNode->data = data;
		newNode->next = NULL;

		if (empty()) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		size++;
		print();
	}
	void insert(int index, int data) {
		if (index < 0 || index > size) {
			cout << "Index Error\n";
		}
		else if (index == size) {
			append(data);
		}
		else if (index == 0) {
			node* newNode = new node;
			newNode->data = data;
			newNode->next = head;
			head = newNode;
			size++;
			print();
		}
		else {
			node* newNode = new node;
			newNode->data = data;
			node* curNode = head;
			for (int i = 1; i < index; i++) {
				curNode = curNode->next;
			}
			newNode->next = curNode->next;
			curNode->next = newNode;
			size++;
			print();
		}
	}
	void remove(int index) {
		if (empty() || index < 0 || index >= size) {
			cout << "-1\n";
		}
		else {
			node* curNode = head;
			if (index == 0) {
				if (size == 1) {
					head = tail = NULL;
				}
				else {
					head = head->next;
				}
			}
			else {
				node* preNode = head;
				for (int i = 0; i < index; i++) {
					preNode = curNode;
					curNode = curNode->next;
				}
				preNode->next = curNode->next;
				if (curNode == tail) {
					tail = preNode;
				}
			}
			cout << curNode->data << "\n";
			delete curNode;
			size--;
		}
	}
	void print() {
		if (empty()) {
			cout << "empty\n";
		}
		else {
			node* curNode = head;
			while (curNode != NULL) {
				cout << curNode->data << " ";
				curNode = curNode->next;
			}
			cout << "\n";
		}
	}
	void sum() {
		if (empty()) {
			cout << "empty\n";
		}
		else {
			int sum = 0;
			node* curNode = head;
			while (curNode != NULL) {
				sum += curNode->data;
				curNode = curNode->next;
			}
			cout << sum << "\n";
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

	LinkedList l = LinkedList();
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
			l.remove(i);
		}
		else if (command == "Print") {
			l.print();
		}
		else if (command == "Insert") {
			int i, x;
			cin >> i >> x;
			l.insert(i, x);
		}
		else if (command == "Sum") {
			l.sum();
		}
	}
}