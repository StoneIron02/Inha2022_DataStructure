#include <iostream>
#include <string>
using namespace std;

template <typename type>
class Queue {
public:
	Queue(int N) {
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
	const type& front() {
		if (empty())
			return NULL; // QueueEmpty
		return arr[f];
	}
	const type& rear() {
		if (empty())
			return NULL; // QueueEmpty
		return arr[(r - 1 + N) % N];
	}
	void enqueue(const type& data) {
		if (size() == N) {
			cout << "Full" << endl;
			return; // QueueFull
		}
		arr[r] = data;
		r = (r + 1) % N;
		n++;
	}
	const type& dequeue() {
		if (empty())
			return NULL; // QueueEmpty
		int data = arr[f];
		f = (f + 1) % N;
		n--;
		return data;
	}
private:
	type* arr;
	int N;
	int n;
	int f, r;
};

int main() {
	int n, t;
	cin >> n >> t;
	Queue<int> queue = Queue<int>(n);
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "isEmpty") {
			switch (queue.empty()) {
			case true:
				cout << "True\n";
				break;
			case false:
				cout << "False\n";
				break;
			}
		}
		else if (command == "size") {
			cout << queue.size() << "\n";
		}
		else if (command == "dequeue") {
			int data = queue.dequeue();
			if (data == NULL)
				cout << "Empty" << endl;
			else
				cout << data << endl;
		}
		else if (command == "enqueue") {
			int data;
			cin >> data;
			queue.enqueue(data);
		}
		else if (command == "front") {
			int data = queue.front();
			if (data == NULL)
				cout << "Empty" << endl;
			else
				cout << data << endl;
		}
		else if (command == "rear") {
			int data = queue.rear();
			if (data == NULL)
				cout << "Empty" << endl;
			else
				cout << data << endl;
		}
	}
}