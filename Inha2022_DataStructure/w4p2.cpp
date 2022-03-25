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
	int dequeue() {
		if (isEmpty()) {
			return -1;
		}
		node* curNode = frontNode;
		if (size() == 1) {
			frontNode = rearNode = NULL;
		}
		else {
			frontNode = curNode->next;
		}
		int data = curNode->data;
		delete curNode;
		n--;
		return data;
	}
private:
	node* frontNode;
	node* rearNode;
	int n;
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int num;
		cin >> num;
		Queue p1 = Queue();
		Queue p2 = Queue();
		int p1Score = 0, p2Score = 0;
		int p1RemainHealth = 0, p2RemainHealth = 0;
		for (int j = 0; j < num; j++) {
			int health;
			cin >> health;
			p1.enqueue(health);
		}
		for (int j = 0; j < num; j++) {
			int health;
			cin >> health;
			p2.enqueue(health);
		}
		for (int j = 0; j < num; j++) {
			cout << "Round" << j + 1 << " ";
			int remain = (p1.dequeue() + p1RemainHealth) - (p2.dequeue() + p2RemainHealth);
			if (remain > 0) { // p1
				cout << ++p1Score << ":" << p2Score << "\n";
				p1RemainHealth = remain;
				p2RemainHealth = 0;
			} else if (remain < 0) { // p2
				cout << p1Score << ":" << ++p2Score << "\n";
				p1RemainHealth = 0;
				p2RemainHealth = -remain;
			}
			else if (remain == 0) { // ¹«
				cout << p1Score << ":" << p2Score << "\n";
				p1RemainHealth = 0;
				p2RemainHealth = 0;
			}
		}
		
		if (p1Score > p2Score) {
			cout << "Winner P1\n";
		} else if (p1Score < p2Score) {
			cout << "Winner P2\n";
		} else if (p1Score == p2Score) {
			cout << "Draw\n";
		}
	}
}