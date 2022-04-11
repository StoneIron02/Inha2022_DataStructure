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
		f = r = NULL;
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	const type& front() {
		if (empty())
			return NULL; // QueueEmpty
		return f->data;
	}
	const type& rear() {
		if (empty())
			return NULL; // QueueEmpty
		return r->data;
	}
	void enqueue(const type& data) {
		node* newNode = new node;
		newNode->data = data;
		newNode->next = NULL;
		if (empty()) {
			f = r = newNode;
		}
		else {
			r->next = newNode;
			r = newNode;
		}
		n++;
	}
	const type& dequeue() {
		if (empty())
			return NULL; // QueueEmpty
		node* curNode = f;
		if (n == 1) {
			f = r = NULL;
		}
		else {
			f = curNode->next;
		}
		type data = curNode->data;
		delete curNode;
		n--;
		return data;
	}
private:
	node* f;
	node* r;
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
			switch (queue.empty()) {
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
			int data = queue.dequeue();
			if (data == NULL)
				cout << "Empty" << endl;
			else
				cout << data << endl;
		}
		else if (command == "enqueue") {
			int data;
			cin >> data;
			queue.enqueue(data);
		}
		else if (command == "front") {
			int data = queue.front();
			if (data == NULL)
				cout << "Empty" << endl;
			else
				cout << data << endl;
		}
		else if (command == "rear") {
			int data = queue.rear();
			if (data == NULL)
				cout << "Empty" << endl;
			else
				cout << data << endl;
		}
	}
}