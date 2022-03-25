#include <iostream>
#include <string>
using namespace std;

class Queue {
public:
	Queue(int capacity) {
		this->capacity = capacity;
		arr = new int[capacity];
		frontIndex = rearIndex = 0;
		n = 0;
	}
	int size() {
		return n;
	}
	bool isEmpty() {
		return (size() == 0);
	}
	void enqueue(int data) {
		if (size() == capacity) {
			cout << "Full\n";
		}
		else {
			arr[rearIndex] = data;
			rearIndex = (rearIndex + 1) % capacity;
			n++;
		}
	}
	int dequeue() {
		if (isEmpty()) {
			cout << "Empty\n";
			return -1;
		}
		int data = arr[frontIndex];
		frontIndex = (frontIndex + 1) % capacity;
		n--;
		return data;
	}
	void front() {
		if (isEmpty()) {
			cout << "Empty\n";
		}
		else {
			cout << arr[frontIndex] << "\n";
		}
	}
	void rear() {
		if (isEmpty()) {
			cout << "Empty\n";
		}
		else {
			cout << arr[(rearIndex - 1 + capacity) % capacity] << "\n";
		}
	}
private:
	int* arr;
	int capacity;
	int frontIndex;
	int rearIndex;
	int n;
};

int main() {
	int n, t;
	cin >> n >> t;
	Queue queue = Queue(n);
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
			int data = queue.dequeue();
			if (data != -1)
				cout << data << "\n";
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