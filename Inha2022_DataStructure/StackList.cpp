#include <iostream>
#include <string>
using namespace std;

typedef int type;
struct node {
	type data;
	node* next;
};

class Stack {
public:
	Stack() {
		head = NULL;
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	void push(type data) {
		node* newNode = new node();
		newNode->data = data;
		newNode->next = head;
		head = newNode;
		n++;
	}
	type pop() {
		if (empty()) {
			// StackEmpty
			return NULL;
		}
		node* curNode = head;
		head = curNode->next;
		type data = curNode->data;
		delete curNode;
		n--;
		return data;
	}
	type top() {
		if (empty()) {
			// StackEmpty
			return NULL;
		}
		return head->data;
	}
	void print() { // Check
		node* curNode = head;
		while (curNode != NULL) {
			cout << curNode->data << " ";
			curNode = curNode->next;
		}
		cout << endl;
	}
private:
	node* head;
	int n;
};

int main() {
	Stack stack = Stack();
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << stack.size() << endl;
		}
		else if (command == "empty") {
			cout << stack.empty() << endl;
		}
		else if (command == "push") {
			int x;
			cin >> x;
			stack.push(x);
		}
		else if (command == "pop") {
			cout << stack.pop() << endl;
		}
		else if (command == "top") {
			cout << stack.top() << endl;
		}
		else if (command == "print") {
			stack.print();
		}
	}
}