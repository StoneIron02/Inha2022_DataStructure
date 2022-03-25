#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* next;
};

class Queue {
public:
	Queue() {
		frontNode = rearNode = NULL;
		n = 0;
	}
	int size() {
		return n;
	}
	bool isEmpty() {
		return (size() == 0);
	}
	void enqueue(int data) {
		node* newNode = new node;
		newNode->data = data;
		newNode->next = NULL;
		if (isEmpty()) {
			frontNode = rearNode = newNode;
		}
		else {
			rearNode->next = newNode;
			rearNode = newNode;
		}
		n++;
	}
	void dequeue() {
		if (isEmpty()) {
			cout << "Empty\n";
			return;
		}
		node* curNode = frontNode;
		if (size() == 1) {
			frontNode = rearNode = NULL;
		}
		else {
			frontNode = curNode->next;
		}
		cout << curNode->data << "\n";
		delete curNode;
		n--;
	}
	void front() {
		if (isEmpty()) {
			cout << "Empty\n";
		}
		else {
			cout << frontNode->data << "\n";
		}
	}
	void rear() {
		if (isEmpty()) {
			cout << "Empty\n";
		}
		else {
			cout << rearNode->data << "\n";
		}
	}
private:
	node* frontNode;
	node* rearNode;
	int n;
};

int main() {
	int t;
	cin >> t;
	Queue queue = Queue();
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "isEmpty") {
			switch (queue.isEmpty()) {
			case true:
				cout << "True\n";
				break;
			case false:
				cout << "False\n";
				break;
			}
		}
		else if (command == "size") {
			cout << queue.size() << "\n";
		}
		else if (command == "dequeue") {
			queue.dequeue();
		}
		else if (command == "enqueue") {
			int data;
			cin >> data;
			queue.enqueue(data);
		}
		else if (command == "front") {
			queue.front();
		}
		else if (command == "rear") {
			queue.rear();
		}
	}
}