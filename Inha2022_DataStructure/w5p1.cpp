#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* prev;
	node* next;
};

node* p;

class List {
public:
	List() {
		header = new node();
		trailer = new node();
		header->next = trailer;
		trailer->prev = header;
		n = 0;
	}
	bool empty() {
		return (n == 0);
	}
	void begin() {
		p = header->next;
	}
	void end() {
		p = trailer;
	}
	void insert(int data) {
		node* newNode = new node();
		newNode->data = data;

		node* nextNode = p;
		node* prevNode = p->prev;

		newNode->prev = prevNode;
		newNode->next = nextNode;
		prevNode->next = newNode;
		nextNode->prev = newNode;
		n++;
	}
	void erase() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}
		if (p == trailer) {
			return;
		}
		node* nextNode = p->next;
		node* prevNode = p->prev;
		
		nextNode->prev = prevNode;
		prevNode->next = nextNode;
		delete p;
		n--;
		begin();
	}
	void nextP() {
		if (p == trailer)
			return;
		p = p->next;
	}
	void prevP() {
		if (p == header->next)
			return;
		p = p->prev;
	}
	void print() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}
		node* curNode = header->next;
		while (curNode != trailer) {
			cout << curNode->data << " ";
			curNode = curNode->next;
		}
		cout << "\n";
	}
	void upper(int data) {
		int index = 0;
		bool printed = false;
		node* curNode = header->next;
		while (curNode != trailer) {
			if (curNode->data == data) {
				cout << index << " ";
				printed = true;
			}
			curNode = curNode->next;
			index++;
		}
		if (!printed)
			cout << -1 << "\n";
		else
			cout << "\n";
	}
private:
	node* header;
	node* trailer;
	int n;
};

int main() {
	List list = List();
	list.begin();

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "find") {
			int data;
			cin >> data;
			list.upper(data);
		}
		else if (command == "begin") {
			list.begin();
		}
		else if (command == "end") {
			list.end();
		}
		else if (command == "insert") {
			int data;
			cin >> data;
			list.insert(data);
		}
		else if (command == "erase") {
			list.erase();
		}
		else if (command == "nextP") {
			list.nextP();
		}
		else if (command == "prevP") {
			list.prevP();
		}
		else if (command == "print") {
			list.print();
		}
	}
}