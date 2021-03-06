#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		return e1 < e2;
	}
};

class Heap {
public:
	Heap() {
		arr.push_back(0);
		arr.push_back(1);
		arr.push_back(5);
		arr.push_back(3);
		arr.push_back(7);
		arr.push_back(9);
		arr.push_back(8);
	}
	int size() {
		return (arr.size() - 1);
	}
	bool empty() {
		return (size() == 0);
	}
	void insert(int data) {
		arr.push_back(data);
		upHeap(size());
	}
	int min() {
		if (empty()) {
			return -1;
		}
		return arr[1];
	}
	int removeMin() {
		if (empty()) {
			return -1;
		}
		int data = arr[1];
		swap(1, size());
		arr.pop_back();
		downHeap(1);
		return data;
	}
	void print() {
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

		if (left > size()) { // 둘 다 존재 X
			return;
		}
		else if (left == size()) { // left만 존재
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
	Heap pq = Heap();
	int item;
	cin >> item;
	pq.print();
	pq.insert(item);
	pq.print();
}