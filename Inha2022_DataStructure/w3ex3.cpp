#include <iostream>
#include <string>
using namespace std;

class Stack {
public:
	Stack(int maxSize) {
		arr = new char[maxSize];
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
	void push(char data) {
		if (size() == maxSize)
			return;
		else {
			arr[++topIndex] = data;
		}
	}
	char pop() {
		if (empty())
			return NULL;
		else {

			topIndex--;
		}
	}
private:
	int maxSize;
	int topIndex;
	char* arr;
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

int grade(char c) {
	switch (c) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
}

int main() {
	string before;
	cin >> before;
	Stack beforeToAfter = Stack(before.size());
	string result = "";
	for (int i = 0; i < before.size(); i++) {
		if (isOperator(before[i])) {
			while (grade(beforeToAfter.top()) > grade(before[i])) {
				result.append("" + )
			}
		}
		else {
			result.append("" + before[i]);
		}
	}




	result.append("");
}