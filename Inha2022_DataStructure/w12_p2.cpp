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
	bool isLogIn;
	entry() {
		key = 0;
		value = "";
		valid = NOITEM;
		isLogIn = false;
	}
	entry(int key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
		isLogIn = false;
	}
	void erase() {
		valid = AVAILABLE;
		isLogIn = false;
	}
};

class HashTable {
public:
	HashTable(int N, int q) {
		this->N = N;
		this->q = q;
		table = new entry[N];
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
	void signup(string s, string p) {
		int key = hashCode(s);
		if (find(key) != "None") {
			cout << "Invalid" << endl;
			return;
		}

		put(key, p);
		cout << "Submit" << endl;
	}
	void login(string s, string p) {
		int key = hashCode(s);
		int index = hashFunction(key);
		int probe = 1;

		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				if (table[index].value == p) {
					if (table[index].isLogIn) {
						cout << "Quit" << endl;
					}
					else {
						table[index].isLogIn = true;
						cout << "Submit" << endl;
					}
				}
				else {
					cout << "Invalid" << endl;
				}
				return;
			}
			index = hashFunction(index + doubleFunction(key));
			probe++;
		}
		cout << "Invalid" << endl;
	}
	void logout(string s) {
		int key = hashCode(s);
		int index = hashFunction(key);
		int probe = 1;

		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				table[index].isLogIn = false;
				cout << "Submit" << endl;
				return;
			}
			index = hashFunction(index + doubleFunction(key));
			probe++;
		}
	}
private:
	entry* table;
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
		if (command == "signup") {
			string s;
			string p;
			cin >> s >> p;
			ht.signup(s, p);
		}
		else if (command == "login") {
			string s;
			string p;
			cin >> s >> p;
			ht.login(s, p);
		}
		else if (command == "logout") {
			string s;
			cin >> s;
			ht.logout(s);
		}
	}
}