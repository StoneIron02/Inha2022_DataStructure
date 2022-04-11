#include <iostream>
#include <string>
using namespace std;

template <typename type>
class Stack {
public:
	Stack(int N) {
		this->N = N;
		arr = new type[N];
		t = -1;
	}
	int size() {
		return t + 1;
	}
	bool empty() {
		return (t < 0);
	}
	void push(const type& data) {
		if (size() == N)
			return; // StackFull
		arr[++t] = data;
	}
	const type& pop() {
		if (empty())
			return NULL; // StackEmpty
		return arr[t--];
	}
	const type& top() {
		if (empty())
			return NULL; // StackEmpty
		return arr[t];
	}
private:
	type* arr;
	int N;
	int t;
};

int main() {
	int t, n;
	cin >> t >> n;
	Stack<int> stack = Stack<int>(t);
	for (int i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << stack.size() << endl;
		}
		else if (command == "empty") {
			cout << int(stack.empty()) << endl;
		}
		else if (command == "push") {
			int x;
			cin >> x;
			stack.push(x);
		}
		else if (command == "pop") {
			int pop = stack.pop();
			if (pop == NULL)
				pop = -1;
			cout << pop << endl;
		}
		else if (command == "top") {
			int top = stack.top();
			if (top == NULL)
				top = -1;
			cout << top << endl;
		}
	}
}