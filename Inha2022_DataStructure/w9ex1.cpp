#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		return e1 < e2;
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
	int min() {
		if (empty()) {
			return -1;
		}

		compare C;
		int maxPriorityIndex = 0;

		for (int i = 0; i < seq.size(); i++) {
			if (C(seq[i], seq[maxPriorityIndex]))
				maxPriorityIndex = i;
		}
		return seq[maxPriorityIndex];
	}
	void removeMin() {
		if (empty()) {
			return;
		}

		compare C;
		int maxPriorityIndex = 0;

		for (int i = 0; i < seq.size(); i++) {
			if (C(seq[i], seq[maxPriorityIndex]))
				maxPriorityIndex = i;
		}
		seq.erase(seq.begin() + maxPriorityIndex);
	}
private:
	vector<int> seq;
};

int main() {

}