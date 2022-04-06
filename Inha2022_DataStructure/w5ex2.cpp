#include <iostream>
using namespace std;

struct node {
	int data;
	node* prev;
	node* next;
};

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
		return (size() == 0);
	}
	int size() {
		return n;
	}
	node* begin() {
		return header->next;
	}
	node* end() {
		return trailer;
	}
	void insert(node* pos, int data) {
		node* newNode = new node();
		newNode->data = data;
		
		node* nextNode = pos;
		node* prevNode = nextNode->prev;

		newNode->next = nextNode;
		newNode->prev = prevNode;
		nextNode->prev = newNode;
		prevNode->next = newNode;

		n++;
	}
	void insertFront(int data) {
		insert(begin(), data);
	}
	void insertBack(int data) {
		insert(end(), data);
	}
	void erase(node* pos) {
		node* nextNode = pos->next;
		node* prevNode = pos->prev;

		nextNode->prev = prevNode;
		prevNode->next = nextNode;
		delete pos;
		n--;
	}
	void eraseFront() {
		erase(begin());
	}
	void eraseBack() {
		erase(end()->prev);
	}
private:
	node* header;
	node* trailer;
	int n;
};

int main() {
	List list = List();
	node* p = list.begin();

	list.insert(p, 4);
	cout << list.size() << "\n";

	list.erase(p->prev);
	p = list.begin();
	cout << list.size() << "\n";

	if (p != list.end())
		p = p->next;

	if (p != list.begin())
		p = p->prev;
}