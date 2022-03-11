#include <iostream>
#include <string>
using namespace std;

class Array {
public:
	Array(int size) {
		this->size = size;
		arr = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = 0;
		}
	}
	void add(int index, int value) {
		for (int i = size - 2; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = value;
	}
	void remove(int index) {
		for (int i = index; i <= size - 2; i++) {
			arr[i] = arr[i + 1];
		}
		arr[size - 1] = 0;
	}
	void set(int index, int value) {
		arr[index] = value;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << "\n";
	}
	void find(int value) {
		for (int i = 0; i < size; i++) {
			if (arr[i] == value) {
				cout << i << endl;
				return;
			}
		}
		cout << -1 << endl;
	}
private:
	int* arr;
	int size;
};

int main() {
	int t, n;
	cin >> t >> n;

	Array arr(n);

	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "add") {
			int i, z;
			cin >> i >> z;
			arr.add(i, z);
		}
		else if (command == "remove") {
			int i;
			cin >> i;
			arr.remove(i);
		}
		else if (command == "set") {
			int i, z;
			cin >> i >> z;
			arr.set(i, z);
		}
		else if (command == "print") {
			arr.print();
		}
		else if (command == "find") {
			int z;
			cin >> z;
			arr.find(z);
		}
	}
}