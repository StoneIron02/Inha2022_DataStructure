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
	void push(const type& data) {
		node* newNode = new node;
		newNode->data = data;
		newNode->next = head;
		head = newNode;
		n++;
	}
	const type& pop() {
		if (empty())
			return NULL; // StackEmpty
		node* curNode = head;
		head = curNode->next;
		type data = curNode->data;
		delete curNode;
		n--;
		return data;
	}
	const type& top() {
		if (empty())
			return NULL; // StackEmpty
		return head->data;
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
		else if (command == "push") {
			int x;
			cin >> x;
			stack.push(x);
		}
		else if (command == "pop") {
			int pop = stack.pop();
			if (pop == NULL)
				pop = -1;
			cout << pop << endl;
		}
		else if (command == "top") {
			int top = stack.top();
			if (top == NULL)
				top = -1;
			cout << top << endl;
		}
	}
}