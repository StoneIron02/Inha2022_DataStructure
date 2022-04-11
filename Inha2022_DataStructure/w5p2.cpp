#include <iostream>
#include <string>
using namespace std;

struct node {
	int data;
	node* prev;
	node* next;
};

class Sequence {
public:
	Sequence() {
		header = new node();
		trailer = new node();
		header->next = trailer;
		trailer->prev = header;
		n = 0;
	}
	bool empty() {
		return (n == 0);
	}
	void append(int data) {
		node* newNode = new node();
		newNode->data = data;

		node* nextNode = trailer;
		node* prevNode = trailer->prev;

		newNode->prev = prevNode;
		newNode->next = nextNode;
		prevNode->next = newNode;
		nextNode->prev = newNode;
		n++;
	}
	void print() {
		node* curNode = header->next;
		while (curNode != trailer) {
			if (curNode == header->next) {
				cout << curNode->data + curNode->next->data << " ";
			}
			else if (curNode == trailer->prev) {
				cout << curNode->data + curNode->prev->data << " ";
			}
			else {
				cout << curNode->data + curNode->next->data + curNode->prev->data << " ";
			}
			curNode = curNode->next;
		}
		cout << "\n";
	}
private:
	node* header;
	node* trailer;
	int n;
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		Sequence list = Sequence();
		for (int j = 0; j < n; j++) {
			int num;
			cin >> num;
			list.append(num);
		}
		list.print();
	}
}