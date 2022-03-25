#include <iostream>
using namespace std;

class Queue {
public:
	Queue(int capacity) {
		this->capacity = capacity;
		arr = new int[capacity];
		frontIndex = rearIndex = 0;
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
		return arr[frontIndex];
	}
	void enqueue(int data) {
		if (size() == capacity) {
			return;
		}
		arr[rearIndex] = data;
		rearIndex = (rearIndex + 1) % capacity;
		n++;
	}
	void dequeue() {
		if (empty()) {
			return;
		}
		frontIndex = (frontIndex + 1) % capacity;
		n--;
	}
private:
	int* arr;
	int capacity;
	int frontIndex;
	int rearIndex;
	int n;
};

int main() {

}