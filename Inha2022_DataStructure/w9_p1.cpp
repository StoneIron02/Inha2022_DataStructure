#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& n1, const int& n2) {
		return n1 < n2;
	}
};

class PQ {
public:
	void insert(int n) {
		compare isHigher;

		int i = 0;
		for (i = 0; i < arr.size(); i++) {
			if (isHigher(arr[i], n))
				break;
		}

		arr.insert(arr.begin() + i, n);
	}
	int pop() {
		int data = arr.back();
		arr.pop_back();
		return data;
	}
private:
	vector<int> arr;
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int N;
		cin >> N;
		PQ pq = PQ();
		for (int j = 0; j < N; j++) {
			int n;
			cin >> n;
			pq.insert(n);
		}
		for (int j = 0; j < N; j++) {
			cout << pq.pop() << " ";
		}
		cout << endl;
	}
}