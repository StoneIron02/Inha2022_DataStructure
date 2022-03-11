#include <iostream>
using namespace std;

class Array {
public:
	Array(int size) {
		arr = new int[size];
		this->size = size;

		for (int i = 0; i < size; i++) {
			arr[i] = 0;
		}
	}
	int at(int index) {
		return arr[index];
	}
	void add(int index, int value) {
		for (int i = size - 2; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = value;
	}
	void set(int index, int value) {
		arr[index] = value;
	}
	void remove(int index) {
		for (int i = index; i <= size - 2; i++) {
			arr[i] = arr[i + 1];
		}
		arr[size - 1] = 0;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
private:
	int* arr;
	int size;
};

int main() {
	Array a(5);

	a.print();
	
	a.add(0, 11);
	a.add(1, 22);
	a.add(2, 33);
	a.set(2, 55);
	a.print();

	cout << a.at(1) << endl;
	cout << a.at(4) << endl;

	a.remove(4);
	a.remove(1);
	a.print();

	a.add(1, 55);
	a.print();

	a.add(4, 77);
	a.print();

	a.add(3, 66);
	a.print();

	a.add(1, 22);
	a.set(3, 88);
	a.print();
}