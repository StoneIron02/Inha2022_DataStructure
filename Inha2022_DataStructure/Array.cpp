#include <iostream>
#include <string>
using namespace std;

typedef int type;
class Array {
public:
	Array(int N) {
		this->N = N;
		arr = new type[N];
		n = 0;
		for (int i = 0; i < N; i++) {
			arr[i] = 0;
		}
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	void append(type data) {
		if (n == N) {
			// ArrayFull
			return;
		}
		arr[n++] = data;
	}
	void insert(int index, type data) {
		if (n == N) {
			// ArrayFull
			return;
		}
		if (index < 0 || index > n) {
			// OutOfIndex
			return;
		}
		else if (index == n) {
			append(data);
		}
		else {
			for (int i = N - 2; i >= index; i--) {
				arr[i + 1] = arr[i];
			}
			arr[index] = data;
			n++;
		}
	}
	void remove(int index) {
		if (empty()) {
			// ArrayEmpty
			return;
		}
		if (index < 0 || index >= n) {
			// OutOfIndex
			return;
		}
		for (int i = index; i <= N - 2; i++) {
			arr[i] = arr[i + 1];
		}
		n--;
	}
	void print() {
		for (int i = 0; i < n; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
private:
	type* arr;
	int n;
	int N;
};

int main() {
	int n;
	cin >> n;
	Array arr = Array(n);
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << arr.size() << endl;
		}
		else if (command == "empty") {
			cout << arr.empty() << endl;
		}
		else if (command == "append") {
			int x;
			cin >> x;
			arr.append(x);
		}
		else if (command == "insert") {
			int x, y;
			cin >> x >> y;
			arr.insert(x, y);
		}
		else if (command == "remove") {
			int x;
			cin >> x;
			arr.remove(x);
		}
		else if (command == "print") {
			arr.print();
		}
	}
}