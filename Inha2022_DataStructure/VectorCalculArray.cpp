#include <iostream>
#include <string>
using namespace std;

typedef int type;
class Vector {
public:
	Vector(int N) {
		this->N = N;
		arr = new int[N];
		f = 0;
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
		return arr[f + index];
	}
	void set(int index, type data) {
		if (index < 0 || index >= n) {
			// OutOfIndex
			return;
		}
		arr[f + index] = data;
	}
	void insert(int index, type data) {
		if (index < 0 || index > n) {
			// OutOfIndex
			return;
		}
		if (n == N) {
			// VectorFull
			return;
		}
		if (index == 0) {
			f = (f - 1 + N) % N;
			arr[f] = data;
		}
		else {
			for (int i = n - 2; i >= index; i--) {
				arr[(f + i + 1) % N] = arr[f + i];
			}
			arr[f] = data;
			f = (f + 1) % N;
		}
		n++;
	}
	void erase(int index) {
		if (index < 0 || index >= n) {
			// OutOfIndex
			return;
		}
		if (empty()) {
			// VectorEmpty
			return;
		}
		if (index == 0) {
			f = (f + 1) % N;
		}
		else {
			for (int i = index; i <= n - 2; i++) {
				arr[f + i] = arr[(f + i + 1) % N];
			}
		}
		n--;
	}
	void print() {
		for (int i = 0; i < n; i++) {
			cout << arr[(f + i) % N] << " ";
		}
		cout << endl;
	}
private:
	type* arr;
	int f;
	int n;
	int N;
};

int main() {
	int n;
	cin >> n;
	Vector vector = Vector(n);
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