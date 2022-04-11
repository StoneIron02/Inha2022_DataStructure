#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* next;
};

class SLinkedList {
public:
	SLinkedList() {
		head = tail = NULL;
		n = 0;
	}
	bool empty() {
		return (n == 0);
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
		n++;
		print();
	}
	void insert(int index, int data) {
		if (index < 0 || index > n) {
			cout << "Index Error\n";
		}
		else if (index == n) {
			append(data);
		}
		else if (index == 0) {
			node* newNode = new node;
			newNode->data = data;
			newNode->next = head;
			head = newNode;
			n++;
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
			n++;
			print();
		}
	}
	void remove(int index) {
		if (empty() || index < 0 || index >= n) {
			cout << "-1\n";
		}
		else {
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
			n--;
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
	void min() {
		if (empty()) {
			cout << "empty\n";
		}
		else {
			int min = head->data;
			node* curNode = head;
			while (curNode != NULL) {
				curNode->data < min ? min = curNode->data : min = min;
				curNode = curNode->next;
			}
			cout << min << "\n";
		}
	}
private:
	node* head;
	node* tail;
	int n;
};

int main() {
	int m;
	cin >> m;

	SLinkedList list = SLinkedList();
	for (int i = 0; i < m; i++) {
		string command;
		cin >> command;
		if (command == "Append") {
			int x;
			cin >> x;
			list.append(x);
		}
		else if (command == "Delete") {
			int i;
			cin >> i;
			list.remove(i);
		}
		else if (command == "Print") {
			list.print();
		}
		else if (command == "Insert") {
			int i, x;
			cin >> i >> x;
			list.insert(i, x);
		}
		else if (command == "Min") {
			list.min();
		}
	}
}