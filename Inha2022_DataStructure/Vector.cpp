#include <iostream>
#include <string>
using namespace std;

template <typename type>
class Vector {
public:
	Vector() {
		N = 1;
		arr = new type[N];
		n = 0;
	}
	const type& operator[](int index) {
		return arr[index];
	}
	int size() {
		return n;
	}
	bool empty() {
		return (n == 0);
	}
	const type& at(int index) {
		if (index < 0 || index >= n)
			return NULL; // OutOfIndex
		return arr[index];
	}
	void set(int index, const type& data) {
		if (index < 0 || index >= n)
			return NULL; // OutOfIndex
		arr[index] = data;
	}
	void insert(int index, const type& data) {
		if (index < 0 || index > n)
			return NULL; // OutOfIndex
		if (n == N)
			reserve(N * 2);
		for (int i = n - 1; i >= index; i--) {
			arr[i + 1] = arr[i];
		}
		arr[index] = data;
		n++;
	}
	const type& erase(int index) {
		if (index < 0 || index >= n)
			return NULL; // OutOfIndex
		type data = arr[index];
		for (int i = index; i <= n - 2; i++) {
			arr[i] = arr[i + 1];
		}
		n--;
		return data;
	}
private:
	type* arr;
	int N;
	int n;
	void reserve(int size) {
		if (size <= N)
			return;
		type* newArray = new type[size];
		for (int i = 0; i < n; i++)
			newArray[i] = arr[i];

		if (arr != NULL)
			delete[] arr;
		arr = newArray;
		N = size;
	}
};

int main() {

}