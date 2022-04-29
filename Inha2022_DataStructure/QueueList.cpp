#include <iostream>
#include <string>
using namespace std;

typedef int type;
struct node {
	type data;
	node* next;
};

class Queue {
public:
	Queue() {
		head = tail = NULL;
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	type front() {
		if (empty()) {
			// QueueEmpty
			return NULL;
		}
		return head->data;
	}
	type rear() {
		if (empty()) {
			// QueueEmpty
			return NULL;
		}
		return tail->data;
	}
	void enqueue(type data) {
		node* newNode = new node();
		newNode->data = data;
		if (empty()) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		n++;
	}
	type dequeue() {
		if (empty()) {
			// QueueEmpty
			return NULL;
		}
		node* curNode = head;
		if (n == 1) {
			head = tail = NULL;
		}
		else {
			head = head->next;
		}
		type data = curNode->data;
		delete curNode;
		n--;
		return data;
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
	node* tail;
	int n;
};

int main() {
	Queue queue = Queue();
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << queue.size() << endl;
		}
		else if (command == "empty") {
			cout << queue.empty() << endl;
		}
		else if (command == "front") {
			cout << queue.front() << endl;
		}
		else if (command == "rear") {
			cout << queue.rear() << endl;
		}
		else if (command == "enqueue") {
			int x;
			cin >> x;
			queue.enqueue(x);
		}
		else if (command == "dequeue") {
			cout << queue.dequeue() << endl;
		}
		else if (command == "print") {
			queue.print();
		}
	}
}