/* insert, erase, indexOf, atIndex´Â ´ú ±¸ÇöµÊ */
#include <iostream>
#include <string>
using namespace std;

typedef int type;
struct node {
	int index;
	type data;
	node(int index, type data) {
		this->index = index;
		this->data = data;
	}
};
class Sequence {
public:
	Sequence(int N) {
		this->N = N;
		arr = new node*[N];
		f = r = 0;
		n = 0;
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	node* begin() {
		return arr[f];
	}
	node* end() {
		return arr[(r - 1 + N) % N];
	}
	void insert(node* pos, type data) {
		if (size() == N) {
			cout << "Full" << endl;
			return; // QueueFull
		}
		int curIndex = (r - 1 + N) % N;
		for (int i = arr[(r - 1 + N) % N]->index; i >= pos->index; i--, curIndex--) {
			arr[(curIndex + 1 + N) % N]->index++;
			arr[(curIndex + 1 + N) % N] = arr[(curIndex + N) % N];
		}
		arr[(curIndex + N) % N] = new node(pos->index, data);
		r = (r + 1) % N;
		n++;
	}
	void insertFront(type data) {
		if (size() == N) {
			cout << "Full" << endl;
			return; // QueueFull
		}
		/* ---------------------------------------------------- */
	}
	void insertBack(type data) {
		if (size() == N) {
			cout << "Full" << endl;
			return; // QueueFull
		}
		arr[r] = new node(n - 1, data);
		r = (r + 1) % N;
		n++;
	}
	/* ---------------------------------------------------- */
private:
	node** arr;
	int N;
	int n;
	int f, r;
};

int main() {
	int n, t;
	cin >> n >> t;
	cout << (-1 % 4);
	Sequence queue = Sequence(n);
}