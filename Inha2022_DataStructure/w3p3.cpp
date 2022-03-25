#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
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
		if (size() == 0)
			return true;
		else
			return false;
	}
	int top() {
		if (empty())
			return -1;
		return head->data;
	}
	void push(int data) {
		node* newNode = new node;
		newNode->data = data;
		newNode->next = head;
		head = newNode;
		n++;
	}
	int pop() {
		if (empty())
			return -1;
		else {
			node* curNode = head;
			head = curNode->next;
			int data = curNode->data;
			delete curNode;
			n--;
			return data;
		}
	}
private:
	node* head;
	int n;
};

int main() {
	int n;
	cin >> n;
	Stack stack = Stack();
	for (int i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << stack.size() << endl;
		}
		else if (command == "empty") {
			cout << int(stack.empty()) << endl;
		}
		else if (command == "top") {
			cout << stack.top() << endl;
		}
		else if (command == "push") {
			int x;
			cin >> x;
			stack.push(x);
		}
		else if (command == "pop") {
			cout << stack.pop() << endl;
		}
	}
}