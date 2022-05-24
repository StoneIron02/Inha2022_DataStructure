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

struct attendance {
	string key;
	int value;
	int valid;
	bool attend;

	attendance() {
		key = "";
		value = 0;
		valid = NOITEM;
		attend = false;
	}

	attendance(string key, int value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
		attend = false;
	}

	void erase() {
		valid = AVAILABLE;
		attend = false;
	}
};

class HashTable {
public:
	HashTable(int N, int q) {
		this->N = N;
		this->q = q;
		table_id = new entry[N];
		table_attendance = new attendance[N];
	}
	void put(int key, string value) {
		int index = hashFunction(key);
		int probe = 1;

		while (table_id[index].valid == ISITEM && probe <= N) {
			index = hashFunction(index + hashFunction2(key));
			probe++;
		}

		if (probe > N) {
			cout << probe << endl;
		}
		table_id[index] = entry(key, value);
		put(value, key);
	}
	void erase(int key) {
		int index = hashFunction(key);
		int probe = 1;

		while (table_id[index].valid != NOITEM && probe <= N) {
			if (table_id[index].valid == ISITEM && table_id[index].key == key) {
				erase(table_id[index].value);
				table_id[index].erase();
				return;
			}
			index = hashFunction(index + hashFunction2(key));
			probe++;
		}
	}
	string find(int key) {
		int index = hashFunction(key);
		int probe = 1;

		while (table_id[index].valid != NOITEM && probe <= N) {
			if (table_id[index].valid == ISITEM && table_id[index].key == key) {
				return table_id[index].value;
			}
			index = hashFunction(index + hashFunction2(key));
			probe++;
		}
		return "None";
	}
	void put(string key, int value) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table_attendance[index].valid == ISITEM && probe <= N) {
			index = hashFunction(index + 1);
			probe++;
		}

		if (probe > N) {
			cout << probe << endl;
		}
		table_attendance[index] = attendance(key, value);
	}
	void erase(string key) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table_attendance[index].valid != NOITEM && probe <= N) {
			if (table_attendance[index].valid == ISITEM && table_attendance[index].key == key) {
				table_attendance[index].erase();
				return;
			}
			index = hashFunction(index + 1);
			probe++;
		}
	}
	void present(string key) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table_attendance[index].valid != NOITEM && probe <= N) {
			if (table_attendance[index].valid == ISITEM && table_attendance[index].key == key) {
				cout << table_attendance[index].value << endl;
				table_attendance[index].attend = true;
				return;
			}
			index = hashFunction(index + 1);
			probe++;
		}
		cout << "Invalid" << endl;
	}
	void absent(string key) {
		int index = hashFunction(hashCode(key));
		int probe = 1;

		while (table_attendance[index].valid != NOITEM && probe <= N) {
			if (table_attendance[index].valid == ISITEM && table_attendance[index].key == key) {
				cout << table_attendance[index].value << endl;
				table_attendance[index].attend = false;
				return;
			}
			index = hashFunction(index + 1);
			probe++;
		}
		cout << "Invalid" << endl;
	}
	int getPresent() {
		int result = 0;
		for (int i = 0; i < N; i++) {
			if (table_attendance[i].valid == ISITEM && table_attendance[i].attend) {
				result++;
			}
		}
		return result;
	}
private:
	entry* table_id;
	attendance* table_attendance;
	int N;
	int q;
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
	int hashFunction2(int key) {
		return q - (key % q);
	}
};

int main() {
	int t;
	cin >> t;
	HashTable ht = HashTable(200003, 83);
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "add") {
			int key;
			string value;
			cin >> key >> value;
			ht.put(key, value);
		}
		else if (command == "delete") {
			int key;
			cin >> key;
			ht.erase(key);
		}
		else if (command == "name") {
			int key;
			cin >> key;
			cout << ht.find(key) << endl;
		}
		else if (command == "present") {
			string value;
			cin >> value;
			ht.present(value);
		}
		else if (command == "absent") {
			string value;
			cin >> value;
			ht.absent(value);
		}
	}
	cout << ht.getPresent() << endl;
}