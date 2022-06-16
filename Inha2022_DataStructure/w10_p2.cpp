#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& n1, const int& n2) {
		return n1 >= n2;
	}
};

class Heap {
public:
	Heap(int p) {
		seq.push_back(0);
		this->p = p;
	}
	int size() {
		return seq.size() - 1;
	}
	bool isEmpty() {
		return size() == 0;
	}
	void insert(int i) {
		seq.push_back(i);
		upHeap(size());
	}
	int pop() {
		if (isEmpty()) {
			return -1;
		}
		int data = seq[1];
		seq[1] = seq.back();
		seq.pop_back();
		downHeap(1);
		return data;
	}
	int top() {
		if (isEmpty()) {
			return -1;
		}
		return seq[1];
	}
	void print() {
		if (isEmpty()) {
			cout << -1 << endl;
			return;
		}
		for (int i = 1; i < seq.size(); i++) {
			cout << seq[i] << " ";
		}
		cout << endl;
	}
	bool isCorrect() {
		for (int i = 1; i < seq.size(); i++) {
			if (seq[i] > p)
				return false;
		}
		return true;
	}
private:
	vector<int> seq;
	int p;
	void swap(int index1, int index2) {
		seq[0] = seq[index1];
		seq[index1] = seq[index2];
		seq[index2] = seq[0];
	}
	void upHeap(int index) {
		if (index == 1)
			return;
		int parentIndex = index / 2;
		compare isHigher;
		if (isHigher(seq[index], seq[parentIndex])) {
			swap(index, parentIndex);
			upHeap(parentIndex);
		}
	}
	void downHeap(int index) {
		int leftChildIndex = index * 2;
		int rightChildIndex = index * 2 + 1;

		compare isHigher;

		int childIndex;
		if (size() < leftChildIndex)
			return;
		else if (size() == leftChildIndex) {
			childIndex = leftChildIndex;
		}
		else {
			if (isHigher(seq[leftChildIndex], seq[rightChildIndex]))
				childIndex = leftChildIndex;
			else
				childIndex = rightChildIndex;
		}

		if (isHigher(seq[childIndex], seq[index])) {
			swap(childIndex, index);
			downHeap(childIndex);
		}
	}
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n, p;
		cin >> n >> p;
		Heap heap = Heap(p);
		for (int j = 0; j < n; j++) {
			int k;
			cin >> k;
			heap.insert(k);
		}
		int count = 0;
		while (true) {
			if (heap.isCorrect()) {
				cout << count << endl;
				heap.print();
				break;
			}
			if (heap.size() < 3) {
				if (heap.isCorrect()) {
					cout << count << endl;
					heap.print();
				}
				else {
					cout << "False" << endl;
				}
				break;
			}

			int n1 = heap.pop();
			int n2 = heap.pop();
			int n3 = heap.pop();
			int max = n1;
			n2 > max ? max = n2 : max = max;
			n3 > max ? max = n3 : max = max;
			int min = n1;
			n2 < min ? min = n2 : min = min;
			n3 < min ? min = n3 : min = min;
			int n = (max + min) / 2;
			heap.insert(n);
			count++;
		}
	}
}