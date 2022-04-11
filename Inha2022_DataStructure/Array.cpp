#include <iostream>
#include <string>
using namespace std;

class Array {
public:
	Array(int N) {
		this->N = N;
		arr = new int[N];
		for (int i = 0; i < N; i++) {
			arr[i] = 0;
		}
	}
	void insert(int index, int data) {
		for (int i = N - 2; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = data;
	}
	void remove(int index) {
		for (int i = index; i <= N - 2; i++) {
			arr[i] = arr[i + 1];
		}
	}
	void set(int index, int data) {
		arr[index] = data;
	}
	void print() {
		for (int i = 0; i < N; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	void find(int data) {
		for (int i = 0; i < N; i++) {
			if (arr[i] == data) {
				cout << i << endl;
				return;
			}
		}
		cout << -1 << endl;
	}
private:
	int* arr;
	int N;
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
			arr.insert(i, z);
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