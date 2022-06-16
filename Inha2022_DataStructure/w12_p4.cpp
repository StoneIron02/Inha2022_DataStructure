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

struct entry2 {
	string key;
	int value;
	int valid;
	bool attendance;
	entry2() {
		key = "";
		value = 0;
		valid = NOITEM;
		attendance = false;
	}
	entry2(string key, int value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
		attendance = false;
	}
	void erase() {
		valid = AVAILABLE;
		attendance = false;
	}
};

class HashTable {
public:
	HashTable(int N, int q) {
		this->N = N;
		this->q = q;
		table = new entry[N];
		table2 = new entry2[N];
	}
	void put(int key, string value) {
		int index = hashFunction(key);
		int probe = 1;

		while (table[index].valid == ISITEM && probe <= N) {
			index = hashFunction(index + doubleFunction(key));
			probe++;
		}

		if (probe > N) {
			return;
		}
		table[index] = entry(key, value);
		put2(value, key);
	}
	void erase(int key) {
		int index = hashFunction(key);
		int probe = 1;

		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				string value = table[index].value;
				table[index].erase();
				erase2(value);
				return;
			}
			index = hashFunction(index + doubleFunction(key));
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
			index = hashFunction(index + doubleFunction(key));
			probe++;
		}
		return "None";
	}
	void put2(string key, int value) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table2[index].valid == ISITEM && probe <= N) {
			index = hashFunction(index + doubleFunction(hashCode(key)));
			probe++;
		}

		if (probe > N) {
			return;
		}
		table2[index] = entry2(key, value);
	}
	void erase2(string key) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table2[index].valid != NOITEM && probe <= N) {
			if (table2[index].valid == ISITEM && table2[index].key == key) {
				table2[index].erase();
				return;
			}
			index = hashFunction(index + doubleFunction(hashCode(key)));
			probe++;
		}
	}
	void present(string key) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table2[index].valid != NOITEM && probe <= N) {
			if (table2[index].valid == ISITEM && table2[index].key == key) {
				table2[index].attendance = true;
				cout << table2[index].value << endl;
				return;
			}
			index = hashFunction(index + doubleFunction(hashCode(key)));
			probe++;
		}
		cout << "Invalid" << endl;
	}
	void absent(string key) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table2[index].valid != NOITEM && probe <= N) {
			if (table2[index].valid == ISITEM && table2[index].key == key) {
				table2[index].attendance = false;
				cout << table2[index].value << endl;
				return;
			}
			index = hashFunction(index + doubleFunction(hashCode(key)));
			probe++;
		}
		cout << "Invalid" << endl;
	}
	void print() {
		int n = 0;
		for (int i = 0; i < N; i++) {
			if (table2[i].valid == ISITEM && table2[i].attendance)
				n++;
		}
		cout << n << endl;
	}
private:
	entry* table;
	entry2* table2;
	int N;
	int q;
	int hashCode(string s) {
		int sum = 0;
		for (int i = 0; i < s.size(); i++) {
			int iChar = s[i] - 'a';
			int pow = 1;
			for (int j = 0; j < i; j++)
				pow *= 26;
			sum += iChar * pow;
		}
		return sum;
	}
	int hashFunction(int k) {
		return k % N;
	}
	int doubleFunction(int k) {
		return q - (k % q);
	}
};

int main() {
	int t;
	cin >> t;
	HashTable ht = HashTable(200003, 7);
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "add") {
			int x;
			string s;
			cin >> x >> s;
			ht.put(x, s);
		}
		else if (command == "delete") {
			int x;
			cin >> x;
			ht.erase(x);
		}
		else if (command == "name") {
			int x;
			cin >> x;
			cout << ht.find(x) << endl;
		}
		else if (command == "present") {
			string s;
			cin >> s;
			ht.present(s);
		}
		else if (command == "absent") {
			string s;
			cin >> s;
			ht.absent(s);
		}
	}
	ht.print();
}