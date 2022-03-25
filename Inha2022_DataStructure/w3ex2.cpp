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
		topNode = NULL;
		listSize = 0;
	}
	bool empty() {
		if (size() == 0)
			return true;
		else
			return false;
	}
	int size() {
		return listSize;
	}
	int top() {
		if (empty())
			return -1;
		else {
			return topNode->data;
		}
	}
	void push(int data) {
		node* newNode = new node();
		newNode->data = data;
		newNode->next = topNode;

		topNode = newNode;
		listSize++;
	}
	void pop() {
		if (empty())
			return;
		else {
			node* curTop = topNode;
			topNode = curTop->next;
			delete curTop;
			listSize--;
		}
	}
private:
	int listSize;
	node* topNode;
};

int main() {

	
}