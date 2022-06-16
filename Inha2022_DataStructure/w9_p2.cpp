#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& n1, const int& n2) {
		if (n1 % 2 == 1 && n2 % 2 == 0)
			return true;
		else if (n1 % 2 == 0 && n2 % 2 == 1)
			return false;
		else {
			return n1 > n2;
		}
	}
};

class PQ {
public:
	void insert(int n) {
		arr.push_back(n);
	}
	int pop() {
		compare isHigher;

		int high = 0;
		for (int i = 0; i < arr.size(); i++) {
			if (isHigher(arr[i], arr[high]))
				high = i;
		}

		int data = arr[high];
		arr.erase(arr.begin() + high);
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