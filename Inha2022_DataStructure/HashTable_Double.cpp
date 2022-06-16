#include <iostream>
#include <string>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

typedef int type;
struct entry {
	type key;
	string value;
	int valid;
	entry() {
		key = 0;
		value = "";
		valid = NOITEM;
	}
	entry(type key, string value) {
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
	HashTable(int N, int q) {
		this->N = N;
		this->q = q;
		table = new entry[N];
	}
	void put(type key, string value) {
		int index = hashFunction(key);
		int probe = 1;
		while (table[index].valid == ISITEM && probe <= N) {
			index = hashFunction(index + hashFunction2(key));
			probe++;
		}

		if (probe > N) {
			// TableFull
			cout << "TABLE FULL" << endl;
			return;
		}
		table[index] = entry(key, value);
	}
	void erase(type key) {
		int index = hashFunction(key);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				cout << table[index].value << endl;
				table[index].erase();
				return;
			}
			index = hashFunction(index + hashFunction2(key));
			probe++;
		}
		cout << "None" << endl;
	}
	string find(type key) {
		int index = hashFunction(key);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				return table[index].value;
			}
			index = hashFunction(index + hashFunction2(key));
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
	int q;
	int hashFunction(int key) {
		return key % N;
	}
	int hashFunction2(int key) {
		return q - (key % q);
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	HashTable ht = HashTable(n, m);
	while (true) {
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