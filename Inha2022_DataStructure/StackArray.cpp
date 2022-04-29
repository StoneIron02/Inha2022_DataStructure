#include <iostream>
#include <string>
using namespace std;

typedef int type;
class Stack {
public:
	Stack(int N) {
		this->N = N;
		arr = new type[N];
		t = -1;
	}
	int size() {
		return (t + 1);
	}
	bool empty() {
		return (t < 0);
	}
	void push(type data) {
		if (size() == N) {
			// StackFull
			return;
		}
		arr[++t] = data;
	}
	type pop() {
		if (empty()) {
			// StackEmpty
			return NULL;
		}
		return arr[t--];
	}
	type top() {
		if (empty()) {
			// StackEmpty
			return NULL;
		}
		return arr[t];
	}
	void print() { // Check
		for (int i = 0; i <= t; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
private:
	type* arr;
	int t;
	int N;
};

int main() {
	int n;
	cin >> n;
	Stack stack = Stack(n);
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << stack.size() << endl;
		}
		else if (command == "empty") {
			cout << stack.empty() << endl;
		}
		else if (command == "push") {
			int x;
			cin >> x;
			stack.push(x);
		}
		else if (command == "pop") {
			cout << stack.pop() << endl;
		}
		else if (command == "top") {
			cout << stack.top() << endl;
		}
		else if (command == "print") {
			stack.print();
		}
	}
}