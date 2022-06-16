#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef int type;
struct compare {
	bool operator()(const type& e1, const type& e2) {
		return e1 < e2;
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
	bool empty() {
		return (size() == 0);
	}
	void insert(type data) {
		arr.push_back(data);
		upHeap(size());
	}
	type top() {
		if (empty()) {
			// HeapEmpty
			return -1;
		}
		return arr[1];
	}
	type pop() {
		if (empty()) {
			// HeapEmpty
			return -1;
		}
		type data = arr[1];
		swap(1, size());
		arr.pop_back();
		downHeap(1);
		return data;
	}
	void print() {
		if (empty()) {
			// HeapEmpty
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
		compare isHigher;
		if (isHigher(arr[index], arr[parent])) {
			swap(index, parent);
			upHeap(parent);
		}
	}
	void downHeap(int index) {
		int left = index * 2;
		int right = index * 2 + 1;
		int child;
		compare isHigher;

		if (left > size()) { // 존재하지 않음
			return;
		}
		else if (left == size()) { // left만 존재
			child = left;
		}
		else { // 둘 다 존재
			if (isHigher(arr[left], arr[right]))
				child = left;
			else
				child = right;
		}

		if (isHigher(arr[child], arr[index])) {
			swap(child, index);
			downHeap(child);
		}
	}
};

int main() {
	Heap heap = Heap();
	while (true) {
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
			cout << heap.empty() << endl;
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