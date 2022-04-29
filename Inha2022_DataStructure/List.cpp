#include <iostream>
#include <string>
using namespace std;

typedef int type;
struct node {
	type data;
	node* prev;
	node* next;
};

class List {
public:
	List() {
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

		newNode->next = nextNode;
		newNode->prev = prevNode;
		nextNode->prev = newNode;
		prevNode->next = newNode;
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