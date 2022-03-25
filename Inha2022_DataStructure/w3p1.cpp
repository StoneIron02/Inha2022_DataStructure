#include <iostream>
#include <string>
using namespace std;

class Stack {
public:
	Stack(int maxSize) {
		this->maxSize = maxSize;
		arr = new int[maxSize];
		topIndex = -1;
	}
	int size() {
		return topIndex + 1;
	}
	bool empty() {
		if (topIndex == -1)
			return true;
		else
			return false;
	}
	int top() {
		if (empty())
			return -1;
		return arr[topIndex];
	}
	void push(int data) {
		if (size() == maxSize)
			cout << "FULL" << endl;
		else
			arr[++topIndex] = data;
	}
	int pop() {
		if (empty())
			return -1;
		else
			return arr[topIndex--];
	}
private:
	int* arr;
	int maxSize;
	int topIndex;
};

int main() {
	int t, n;
	cin >> t >> n;
	Stack stack = Stack(t);
	for (int i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << stack.size() << endl;
		}
		else if (command == "empty") {
			cout << int(stack.empty()) << endl;
		}
		else if (command == "top") {
			cout << stack.top() << endl;
		}
		else if (command == "push") {
			int x;
			cin >> x;
			stack.push(x);
		}
		else if (command == "pop") {
			cout << stack.pop() << endl;
		}
	}
}