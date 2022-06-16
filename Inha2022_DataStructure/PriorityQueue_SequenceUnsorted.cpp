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

class PQ {
public:
	int size() {
		return seq.size();
	}
	bool empty() {
		return seq.empty();
	}
	void insert(type data) {
		seq.push_back(data);
	}
	type top() {
		if (empty()) {
			// SequenceEmpty
			return -1;
		}

		compare isHigher;
		int highPriorityIndex = 0;
		for (int i = 0; i < seq.size(); i++) {
			if (isHigher(seq[i], seq[highPriorityIndex]))
				highPriorityIndex = i;
		}
		type data = seq[highPriorityIndex];
		return data;
	}
	type pop() {
		if (empty()) {
			// SequenceEmpty
			return -1;
		}

		compare isHigher;
		int highPriorityIndex = 0;
		for (int i = 0; i < seq.size(); i++) {
			if (isHigher(seq[i], seq[highPriorityIndex]))
				highPriorityIndex = i;
		}
		type data = seq[highPriorityIndex];
		seq.erase(seq.begin() + highPriorityIndex);
		return data;
	}
private:
	vector<int> seq;
};

int main() {
	while (true) {
		int n;
		cin >> n;
		PQ pq = PQ();
		for (int j = 0; j < n; j++) {
			int item;
			cin >> item;
			pq.insert(item);
		}
		for (int j = 0; j < n; j++) {
			cout << pq.pop() << " ";
		}
		cout << endl;
	}
}