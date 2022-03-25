#include <iostream>
#include <string>
using namespace std;

class Stack {
public:
	Stack(int maxSize) {
		arr = new int[maxSize];
		this->maxSize = maxSize;
		topIndex = -1;
	}
	bool empty() {
		if (topIndex == -1)
			return true;
		else
			return false;
	}
	int size() {
		return topIndex + 1;
	}
	int top() {
		if (empty())
			return -1;
		else {
			arr[topIndex];
		}
	}
	void push(int data) {
		if (size() == maxSize)
			return;
		else {
			arr[++topIndex] = data;
		}
	}
	void pop() {
		if (empty())
			return;
		else {
			topIndex--;
		}
	}
private:
	int maxSize;
	int topIndex;
	int* arr;
};

int main() {

}