#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		return (e1 > e2);
	}
};

class PQ {
public:
	int size() {
		return seq.size();
	}
	bool empty() {
		return (seq.size() == 0);
	}
	void insert(int data) {
		seq.push_back(data);
	}
	int removeMin() {
		compare C;
		int higherPriorityIndex = 0;
		for (int i = 0; i < seq.size(); i++) {
			if (C(seq[i], seq[higherPriorityIndex]))
				higherPriorityIndex = i;
		}
		int data = seq[higherPriorityIndex];
		seq.erase(seq.begin() + higherPriorityIndex);
		return data;
	}
private:
	vector<int> seq;
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		PQ pq = PQ();
		for (int j = 0; j < n; j++) {
			int item;
			cin >> item;
			pq.insert(item);
		}
		for (int j = 0; j < n; j++) {
			cout << pq.removeMin() << " ";
		}
		cout << endl;
	}
}