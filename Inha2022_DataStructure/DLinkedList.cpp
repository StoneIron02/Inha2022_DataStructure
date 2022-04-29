#include <iostream>
#include <string>
using namespace std;

typedef int type;
struct node {
	type data;
	node* prev;
	node* next;
};

class DLinkedList {
public:
	DLinkedList() {
		header = trailer = new node();
		header->next = trailer;
		trailer->prev = header;
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	void insert(int index, type data) {
		if (index < 0 || index > n) {
			// OutOfIndex
			return;
		}
		node* newNode = new node();
		newNode->data = data;
		node* curNode = header->next;
		for (int i = 0; i < index; i++) {
			curNode = curNode->next;
		}
		node* prevNode = curNode->prev;
		node* nextNode = curNode;
		newNode->prev = prevNode;
		newNode->next = nextNode;
		prevNode->next = newNode;
		nextNode->prev = newNode;
		n++;
	}
	void remove(int index) {
		if (index < 0 || index >= n) {
			// OutOfIndex
			return;
		}
		node* curNode = header->next;
		for (int i = 0; i < index; i++) {
			curNode = curNode->next;
		}
		node* prevNode = curNode->prev;
		node* nextNode = curNode->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		delete curNode;
		n--;
	}
	void print() {
		node* curNode = header->next;
		while (curNode != trailer) {
			cout << curNode->data << " ";
			curNode = curNode->next;
		}
		cout << endl;
	}
private:
	node* header;
	node* trailer;
	int n;
};

int main() {
	DLinkedList list = DLinkedList();
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << list.size() << endl;
		}
		else if (command == "empty") {
			cout << list.empty() << endl;
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