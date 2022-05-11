#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		return (e1 < e2);
	}
};

class Heap {
public:
	Heap() {
		arr.push_back(0);
	}
	int size() {
		return (arr.size() - 1);
	}
	bool isEmpty() {
		return (size() == 0);
	}
	void insert(int e) {
		arr.push_back(e);
		upHeap(size());
	}
	int top() {
		if (isEmpty()) {
			return -1;
		}
		return arr[1];
	}
	int pop() {
		if (isEmpty()) {
			return -1;
		}
		int e = arr[1];
		swap(1, size());
		arr.pop_back();
		downHeap(1);
		return e;
	}
	void print() {
		if (isEmpty()) {
			cout << -1 << endl;
			return;
		}

		for (int i = 1; i < arr.size(); i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
private:
	vector<int> arr;
	void swap(int index1, int index2) {
		arr[0] = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = arr[0];
	}
	void upHeap(int index) {
		if (index == 1)
			return;

		int parent = index / 2;
		compare Compare;
		if (Compare(arr[index], arr[parent])) {
			swap(index, parent);
			upHeap(parent);
		}
	}
	void downHeap(int index) {
		int left = index * 2;
		int right = index * 2 + 1;
		int child;
		compare Compare;

		if (left > size()) {
			return;
		}
		else if (left == size()) {
			child = left;
		}
		else {
			if (Compare(arr[left], arr[right]))
				child = left;
			else
				child = right;
		}

		if (Compare(arr[child], arr[index])) {
			swap(child, index);
			downHeap(child);
		}
	}
};

int main() {
	int t;
	cin >> t;
	Heap heap = Heap();
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "insert") {
			int i;
			cin >> i;
			heap.insert(i);
		}
		else if (command == "size") {
			cout << heap.size() << endl;
		}
		else if (command == "isEmpty") {
			cout << heap.isEmpty() << endl;
		}
		else if (command == "pop") {
			cout << heap.pop() << endl;
		}
		else if (command == "top") {
			cout << heap.top() << endl;
		}
		else if (command == "print") {
			heap.print();
		}
	}
}