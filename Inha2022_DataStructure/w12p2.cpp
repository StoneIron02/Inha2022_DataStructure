#include <iostream>
#include <string>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

struct entry {
	string key;
	string value;
	int valid;
	bool logged;

	entry() {
		key = "";
		value = "";
		valid = NOITEM;
		logged = false;
	}

	entry(string key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
		logged = false;
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
	void put(string key, string value) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table[index].valid == ISITEM && probe <= N) {
			index = hashFunction(index + 1);
			probe++;
		}

		if (probe > N) {
			cout << probe << endl;
		}
		table[index] = entry(key, value);
	}
	void erase(string key) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				table[index].erase();
				return;
			}
			index = hashFunction(index + 1);
			probe++;
		}
	}
	string find(string key) {
		int index = hashFunction(hashCode(key));
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
	void signup(string key, string value) {
		if (find(key) != "None") {
			cout << "Invalid" << endl;
			return;
		}

		put(key, value);
		cout << "Submit" << endl;
	}
	void login(string key, string value) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				break;
			}
			index = hashFunction(index + 1);
			probe++;
		}

		if (table[index].value != value) {
			cout << "Invalid" << endl;
			return;
		}

		if (table[index].logged) {
			cout << "Quit" << endl;
		}
		else {
			cout << "Submit" << endl;
			table[index].logged = true;
		}
	}
	void logout(string key) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table[index].valid != NOITEM && probe <= N) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				break;
			}
			index = hashFunction(index + 1);
			probe++;
		}

		cout << "Submit" << endl;
		table[index].logged = false;
	}
private:
	entry* table;
	int N;
	int hashCode(string key) {
		int result = 0;
		for (int i = 0; i < key.size(); i++) {
			int val = (int)key[i] - 97;
			for (int j = 0; j < i; j++)
				val *= 26;
			result += val;
		}
		return result;
	}
	int hashFunction(int key) {
		return key % N;
	}
};

int main() {
	int t;
	cin >> t;
	HashTable ht = HashTable(200003);
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "signup") {
			string key;
			string value;
			cin >> key >> value;
			ht.signup(key, value);
		}
		else if (command == "login") {
			string key;
			string value;
			cin >> key >> value;
			ht.login(key, value);
		}
		else if (command == "logout") {
			string key;
			cin >> key;
			ht.logout(key);
		}
	}
}