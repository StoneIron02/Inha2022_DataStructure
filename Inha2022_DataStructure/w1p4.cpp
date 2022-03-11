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
	void set(int index, int value) {
		arr[index] = value;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << "\n";
	}
	void shift(int d) {
		for (int i = 0; i < d; i++) {
			int temp;
			temp = arr[0];
			for (int j = 1; j <= size - 1; j++) {
				arr[j - 1] = arr[j];
			}
			arr[size - 1] = temp;
		}
	}
	void reverse(int i, int j) {
		int change_num = j - i + 1;
		int* temp = new int[change_num];
		for (int n = 0; n < change_num; n++) {
			temp[n] = arr[n + i];
		}
		for (int n = 0; n < change_num; n++) {
			arr[j - n] = temp[n];
		}
	}
private:
	int* arr;
	int size;
};

int main() {
	int t, n;
	cin >> t >> n;

	Array arr(n);

	for (int i = 0; i < n; i++) {
		int z;
		cin >> z;
		arr.set(i, z);
	}

	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "shift") {
			int d;
			cin >> d;
			arr.shift(d);
		}
		else if (command == "reverse") {
			int i, j;
			cin >> i >> j;
			arr.reverse(i, j);
		}
		else if (command == "print") {
			arr.print();
		}
	}
}