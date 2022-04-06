#include <iostream>
#include <string>
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
		if (n == 1) {
			cout << 0 << "\n";
			return;
		}
		while (curNode != trailer) {
			if (curNode == header->next) {
				int max = curNode->data, min = curNode->data;
				max < curNode->next->data ? max = curNode->next->data : max = max;
				min > curNode->next->data ? min = curNode->next->data : min = min;
				cout << max - min << " ";
			}
			else if (curNode == trailer->prev) {
				int max = curNode->data, min = curNode->data;
				max < curNode->prev->data ? max = curNode->prev->data : max = max;
				min > curNode->prev->data ? min = curNode->prev->data : min = min;
				cout << max - min << " ";
			}
			else {
				int max = curNode->data, min = curNode->data;
				max < curNode->next->data ? max = curNode->next->data : max = max;
				max < curNode->prev->data ? max = curNode->prev->data : max = max;
				min > curNode->next->data ? min = curNode->next->data : min = min;
				min > curNode->prev->data ? min = curNode->prev->data : min = min;
				cout << max - min << " ";
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
		List list = List();
		for (int j = 0; j < n; j++) {
			int num;
			cin >> num;
			list.append(num);
		}
		list.print();
	}
}