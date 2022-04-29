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
		compare C;
		int i;

		for (i = 0; i < seq.size(); i++) {
			if (C(seq[i], data))
				break;
		}
		seq.insert(seq.begin() + i, data);
	}
	int min() {
		if (empty()) {
			return -1;
		}

		return seq.back();
	}
	void removeMin() {
		if (empty()) {
			return;
		}

		seq.pop_back();
	}
private:
	vector<int> seq;
};

int main() {

}