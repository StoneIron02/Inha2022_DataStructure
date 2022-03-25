#include <iostream>
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
	bool empty() {
		return (n == 0);
	}
	int size() {
		return n;
	}
	int front() {
		if (empty()) {
			return -1;
		}
		return frontNode->data;
	}
	void enqueue(int data) {
		node* newNode = new node;
		newNode->data = data;
		newNode->next = NULL;
		if (empty()) {
			frontNode = rearNode = newNode;
		}
		else {
			rearNode->next = newNode;
			rearNode = newNode;
		}
		n++;
	}
	void dequeue() {
		if (empty()) {
			return;
		}
		node* curNode = frontNode;
		if (size() == 1) {
			frontNode = rearNode = NULL;
		}
		else {
			frontNode = frontNode->next;
		}
		delete curNode;
		n--;
	}
private:
	node* frontNode;
	node* rearNode;
	int n;
};

int main() {

}