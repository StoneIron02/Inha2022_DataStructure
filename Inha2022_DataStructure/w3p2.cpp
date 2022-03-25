#include <iostream>
#include <string>
using namespace std;

class Stack {
public:
	Stack(int maxSize) {
		this->maxSize = maxSize;
		arr = new char[maxSize];
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
	char top() {
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
	char pop() {
		if (empty())
			return NULL;
		else {
			char val = arr[topIndex--];
			return val;
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
	void print(char now) {
		while (!empty()) {
			if (getGrade(now) > getGrade(top())) {
				break;
			}
			cout << pop();
		}
	}
private:
	char* arr;
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
		string before;
		cin >> before;
		Stack s = Stack(before.size());

		for (int j = 0; j < before.size(); j++) {
			if (isOperator(before[j])) {
				s.print(before[j]);
				s.push(before[j]);
			}
			else {
				cout << before[j];
			}
		}
		while (!s.empty()) {
			cout << s.pop();
		}
		
		cout << endl;
	}
}