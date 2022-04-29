#include <iostream>
#include <string>
using namespace std;

typedef int type;
struct node {
	type data;
	node* prev;
	node* next;
};

class Sequence {
public:
	Sequence() {
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
	node* begin() {
		return header->next;
	}
	node* end() {
		return trailer;
	}
	void insert(node* pos, type data) {
		node* newNode = new node();
		newNode->data = data;

		node* prevNode = pos->prev;
		node* nextNode = pos;

		newNode->prev = prevNode;
		newNode->next = nextNode;
		prevNode->next = newNode;
		nextNode->prev = newNode;
		n++;
	}
	void insertFront(type data) {
		insert(begin(), data);
	}
	void insertBack(type data) {
		insert(end(), data);
	}
	void erase(node* pos) {
		node* prevNode = pos->prev;
		node* nextNode = pos->next;

		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		n--;
	}
	void eraseFront() {
		erase(begin());
	}
	void eraseBack() {
		erase(end()->prev);
	}
	node* atIndex(int index) {
		if (index < 0 || index >= n) {
			// OutOfIndex
			return NULL;
		}
		node* curNode = begin();
		for (int i = 0; i < index; i++) {
			curNode = curNode->next;
		}
		return curNode;
	}
	int indexOf(node* pos) {
		node* curNode = begin();
		for (int i = 0; i < n; i++) {
			if (curNode == pos) {
				return i;
			}
		}
		return -1;
	}
	void print() { // Check
		node* curNode = begin();
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
	Sequence sequence = Sequence();
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << sequence.size() << endl;
		}
		else if (command == "empty") {
			cout << sequence.empty() << endl;
		}
		else if (command == "begin") {
			cout << sequence.begin()->data << endl;
		}
		else if (command == "end") {
			cout << sequence.end()->prev->data << endl;
		}
		else if (command == "insert") {
			int x, y;
			cin >> x >> y;
			sequence.insert(sequence.atIndex(x), y);
		}
		else if (command == "insertFront") {
			int y;
			cin >> y;
			sequence.insertFront(y);
		}
		else if (command == "insertBack") {
			int y;
			cin >> y;
			sequence.insertBack(y);
		}
		else if (command == "erase") {
			int x;
			cin >> x;
			sequence.erase(sequence.atIndex(x));
		}
		else if (command == "eraseFront") {
			sequence.eraseFront();
		}
		else if (command == "eraseBack") {
			sequence.eraseBack();
		}
		else if (command == "atIndex") {
			int x;
			cin >> x;
			sequence.atIndex(x);
		}
		else if (command == "print") {
			sequence.print();
		}
	}
}