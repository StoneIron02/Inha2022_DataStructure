#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* prev;
	node* next;
};

class Sequence {
public:
	Sequence() {
		header = trailer = new node;
		header->next = trailer;
		trailer->prev = header;
		n = 0;
	}
	bool empty() {
		return (n == 0);
	}
	void append(int data) {
		node* newNode = new node;
		newNode->data = data;

		node* curNode = trailer->prev;
		newNode->prev = curNode;
		newNode->next = trailer;
		curNode->next = newNode;
		trailer->prev = newNode;
		n++;
		print();
	}
	int remove(int index) {
		if (empty() || index < 0 || index >= n) {
			return -1;
		}
		else {
			node* curNode = header->next;
			for (int i = 0; i < index; i++) {
				curNode = curNode->next;
			}
			node* preNode = curNode->prev;
			node* nextNode = curNode->next;

			preNode->next = nextNode;
			nextNode->prev = preNode;
			int data = curNode->data;
			delete curNode;
			n--;
			return data;
		}
	}
	void print() {
		if (empty()) {
			cout << "empty\n";
		}
		else {
			node* curNode = header->next;
			while (curNode != trailer) {
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
			node* curNode = trailer->prev;
			while (curNode != header) {
				cout << curNode->data << " ";
				curNode = curNode->prev;
			}
			cout << "\n";
		}
	}
	void update(int x, int y) {
		if (empty()) {
			cout << "empty\n";
		}
		else {
			node* curNode = header->next;
			bool found = false;
			while (curNode != trailer) {
				if (curNode->data == x) {
					curNode->data = y;
					found = true;
				}
				curNode = curNode->next;
			}
			if (found) {
				print();
			}
			else {
				cout << "Not found\n";
			}
		}
	}
private:
	node* header;
	node* trailer;
	int n;
};

int main() {
	int m;
	cin >> m;

	Sequence list = Sequence();
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
			cout << list.remove(i) << "\n";
		}
		else if (command == "Print") {
			list.print();
		}
		else if (command == "Print_reverse") {
			list.print_reverse();
		}
		else if (command == "Update") {
			int x, y;
			cin >> x >> y;
			list.update(x, y);
		}
	}
}