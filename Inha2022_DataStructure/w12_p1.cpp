#include <iostream>
#include <string>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

struct entry {
	int key;
	string value;
	int valid;
	entry() {
		key = 0;
		value = "";
		valid = NOITEM;
	}
	entry(int key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
	}
	void erase() {
		valid = AVAILABLE;
	}
};

class HashTable {
public:
	HashTable(int N) {
		this->N = N;
		table = new entry[N];
	}
	void put(int key, string value) {
		int index = hashFunction(key);
		int probe = 1;

		while (table[index].valid == ISITEM && probe <= N) {
			index = hashFunction(index + 1);
			probe++;
		}

		if (probe > N) {
			return;
		}
		table[index] = entry(key, value);
		cout << probe << endl;
	}
	void erase(int key) {
		int index = hashFunction(key);
		int probe = 1;

		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				cout << table[index].value << endl;
				table[index].erase();
				return;
			}
			index = hashFunction(index + 1);
			probe++;
		}
		cout << "None" << endl;
	}
	string find(int key) {
		int index = hashFunction(key);
		int probe = 1;

		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				return table[index].value;
			}
			index = hashFunction(index + 1);
			probe++;
		}
		return "None";
	}
	int vacant() {
		int n = 0;
		for (int i = 0; i < N; i++) {
			if (table[i].valid != ISITEM)
				n++;
		}
		return n;
	}
private:
	entry* table;
	int N;
	int hashFunction(int k) {
		return k % N;
	}
};

int main() {
	int t, N;
	cin >> t >> N;
	HashTable ht = HashTable(N);
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "put") {
			int k;
			string s;
			cin >> k >> s;
			ht.put(k, s);
		}
		else if (command == "erase") {
			int k;
			cin >> k;
			ht.erase(k);
		}
		else if (command == "find") {
			int k;
			cin >> k;
			cout << ht.find(k) << endl;
		}
		else if (command == "vacant") {
			cout << ht.vacant() << endl;
		}
	}
}