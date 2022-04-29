#include <iostream>
#include <string>
using namespace std;

typedef int type;
class Queue {
public:
	Queue(int N) {
		this->N = N;
		arr = new type[N];
		f = r = 0;
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
		return arr[f];
	}
	type rear() {
		if (empty()) {
			// QueueEmpty
			return NULL;
		}
		return arr[(r - 1 + N) % N];
	}
	void enqueue(type data) {
		if (n == N) {
			// QueueFull
			return;
		}
		arr[r] = data;
		r = (r + 1) % N;
		n++;
	}
	type dequeue() {
		if (empty()) {
			// QueueEmpty
			return NULL;
		}
		type data = arr[f];
		f = (f + 1) % N;
		n--;
		return data;
	}
	void print() { // Check
		for (int i = 0; i < n; i++) {
			cout << arr[(f + i) % N] << " ";
		}
		cout << endl;
	}
private:
	type* arr;
	int f, r;
	int n;
	int N;
};

int main() {
	int n;
	cin >> n;
	Queue queue = Queue(n);
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