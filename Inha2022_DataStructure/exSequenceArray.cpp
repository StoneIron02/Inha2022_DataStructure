#include <iostream>
#include <string>
using namespace std;

typedef int type;
class Sequence {
public:
	Sequence(int N) {
		this->N = N;
		arr = new type[N];
		f = r = 0;
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	type begin() {
		if (empty()) {
			// SequenceEmpty
			return NULL;
		}
		return arr[f];
	}
	type end() {
		if (empty()) {
			// SequenceEmpty
			return NULL;
		}
		return arr[(r - 1 + N) % N];
	}
	void insert(int index, type data) {
		if (n == N) {
			// SequenceFull
			return;
		}
		for (int i = n - 1; i >= index; i--) {
			arr[(f + i + 1) % N] = arr[(f + i) % N];
		}
		arr[(f + index) % N] = data;
		r = (r + 1) % N;
		n++;
	}
	void insertFront(type data) {
		if (n == N) {
			// SequenceFull
			return;
		}
		f = (f - 1 + N) % N;
		arr[f] = data;
		n++;
	}
	void insertBack(type data) {
		if (n == N) {
			// SequenceFull
			return;
		}
		arr[r] = data;
		r = (r + 1) % N;
		n++;
	}
	void erase(int index) {
		if (empty()) {
			// SequenceEmpty
			return;
		}
		for (int i = index; i <= n - 2; i++) {
			arr[(f + i) % N] = arr[(f + i + 1) % N];
		}
		r = (r - 1 + N) % N;
		n--;
	}
	void eraseFront() {
		if (empty()) {
			// SequenceEmpty
			return;
		}
		f = (f + 1) % N;
		n--;
	}
	void eraseBack() {
		if (empty()) {
			// SequenceEmpty
			return;
		}
		r = (r - 1 + N) % N;
		n--;
	}
	int atIndex(int index) {
		return ((f + index) % N);
	}
	int indexOf(int pos) {
		return ((pos - f + N) % N);
	}
	void print() {
		for (int i = 0; i < n; i++) {
			cout << arr[(f + i) % N] << " ";
		}
		cout << endl;
	}
private:
	type* arr;
	int f, r;
	int n;
	int N;
};

int main() {
	int n;
	cin >> n;
	Sequence sequence = Sequence(n);
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << sequence.size() << endl;
		}
		else if (command == "empty") {
			cout << sequence.empty() << endl;
		}
		else if (command == "begin") {
			cout << sequence.begin() << endl;
		}
		else if (command == "end") {
			cout << sequence.end() << endl;
		}
		else if (command == "insert") {
			int x, y;
			cin >> x >> y;
			sequence.insert(x, y);
		}
		else if (command == "insertFront") {
			int y;
			cin >> y;
			sequence.insertFront(y);
		}
		else if (command == "insertBack") {
			int y;
			cin >> y;
			sequence.insertBack(y);
		}
		else if (command == "erase") {
			int x;
			cin >> x;
			sequence.erase(x);
		}
		else if (command == "eraseFront") {
			sequence.eraseFront();
		}
		else if (command == "eraseBack") {
			sequence.eraseBack();
		}
		else if (command == "atIndex") {
			int x;
			cin >> x;
			sequence.atIndex(x);
		}
		else if (command == "print") {
			sequence.print();
		}
	}
}