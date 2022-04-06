#include <iostream>
using namespace std;

class Vector {
public:
	Vector() {
		capacity = 1;
		arr = new int[capacity];
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (size() == 0);
	}
	int at(int index) {
		if (index < 0 || index >= size()) {
			return -1;
		}
		return arr[index];
	}
	void set(int index, int data) {
		if (index < 0 || index >= size()) {
			return;
		}
		arr[index] = data;
	}
	void erase(int index) {
		if (index < 0 || index >= size()) {
			return;
		}
		for (int i = index; i <= n - 2; i++) {
			arr[i] = arr[i + 1];
		}
		n--;
	}
	void insert(int index, int data) {
		if (index < 0 || index > size()) {
			return;
		}
		if (capacity == n) {
			reserve(capacity * 2);
		}
		for (int i = n - 1; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = data;
		n++;
	}
private:
	int capacity;
	int n;
	int* arr;
	void reserve(int size) {
		if (size <= capacity) {
			return;
		}
		int* tmp = new int[size];
		for (int i = 0; i < n; i++) {
			tmp[i] = arr[i];
		}
		if (arr != NULL) {
			delete[] arr;
		}
		arr = tmp;
		capacity = size;
	}
};

int main() {

}