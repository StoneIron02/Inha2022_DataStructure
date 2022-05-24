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
			cout << probe << endl;
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
		int empty = 0;
		for (int i = 0; i < N; i++) {
			if (table[i].valid != ISITEM)
				empty++;
		}

		return empty;
	}
private:
	entry* table;
	int N;
	int hashFunction(int key) {
		return key % N;
	}
};

int main() {
	int t, n;
	cin >> t >> n;
	HashTable ht = HashTable(n);
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "put") {
			int key;
			string value;
			cin >> key >> value;
			ht.put(key, value);
		}
		else if (command == "erase") {
			int key;
			cin >> key;
			ht.erase(key);
		}
		else if (command == "find") {
			int key;
			cin >> key;
			cout << ht.find(key) << endl;
		}
		else if (command == "vacant") {
			cout << ht.vacant() << endl;
		}
	}
}