#include <iostream>
#include <string>
using namespace std;

typedef int type;
class Vector {
public:
	Vector() {
		N = 1;
		arr = new type[N];
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	type at(int index) {
		if (index < 0 || index >= n) {
			// OutOfIndex
			return NULL;
		}
		return arr[index];
	}
	void set(int index, type data) {
		if (index < 0 || index >= n) {
			// OutOfIndex
			return;
		}
		arr[index] = data;
	}
	void insert(int index, type data) {
		if (index < 0 || index > n) {
			// OutOfIndex
			return;
		}
		if (n == N) {
			reserve(N * 2);
		}
		for (int i = n - 2; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = data;
		n++;
	}
	void erase(int index) {
		if (empty()) {
			// VectorEmpty
			return;
		}
		if (index < 0 || index >= n) {
			// OutOfIndex
			return;
		}
		for (int i = index; i <= n - 2; i++) {
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
	void reserve(int newSize) {
		type* newArr = new type[newSize];
		for (int i = 0; i < N; i++) {
			newArr[i] = arr[i];
		}
		N = newSize;
		delete[] arr;
		arr = newArr;
	}
};

int main() {
	Vector vector = Vector();
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << vector.size() << endl;
		}
		else if (command == "empty") {
			cout << vector.empty() << endl;
		}
		else if (command == "at") {
			int x;
			cin >> x;
			cout << vector.at(x) << endl;
		}
		else if (command == "set") {
			int x, y;
			cin >> x >> y;
			vector.set(x, y);
		}
		else if (command == "insert") {
			int x, y;
			cin >> x >> y;
			vector.insert(x, y);
		}
		else if (command == "erase") {
			int x;
			cin >> x;
			vector.erase(x);
		}
		else if (command == "print") {
			vector.print();
		}
	}
}