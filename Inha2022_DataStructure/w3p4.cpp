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
			return NULL;
		return arr[topIndex];
	}
	void push(char data) {
		if (size() == maxSize)
			cout << "FULL" << endl;
		else
			arr[++topIndex] = data;
	}
	int pop() {
		if (empty())
			return NULL;
		else {
			return arr[topIndex--];
		}
	}
	int getGrade(char c) {
		switch (c) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		}
	}
	void calculate(char oper) {
		int b = pop();
		int a = pop();
		switch (oper) {
		case '+':
			push(a + b);
			break;
		case '-':
			push(a - b);
			break;
		case '*':
			push(a * b);
			break;
		case '/':
			push(a / b);
			break;
		}
	}
private:
	int* arr;
	int maxSize;
	int topIndex;
};

bool isOperator(char c) {
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
		return true;
	default:
		return false;
	}
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		string after;
		cin >> after;
		Stack s = Stack(after.size());

		for (int j = 0; j < after.size(); j++) {
			if (isOperator(after[j])) {
				s.calculate(after[j]);
			}
			else {
				s.push(after[j] - '0');
			}
		}
		cout << s.pop() << endl;
	}
}