#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node {
	int data;
	node* parent;
	vector<node*> childs;
	node(int data, node* parent) {
		this->data = data;
		this->parent = parent;
	}
};

class Tree {
public:
	Tree() {
		root = new node(1, NULL);
		nodeList.push_back(root);
	}
	void insert(int parentData, int data) {
		if (find(data, nodeList) != -1) {
			cout << -1 << endl;
			return;
		}
		int index = find(parentData, nodeList);
		if (index == -1) {
			cout << -1 << endl;
			return;
		}
		node* parent = nodeList[index];

		node* newNode = new node(data, parent);
		parent->childs.push_back(newNode);
		nodeList.push_back(newNode);
	}
	void remove(int data) {
		int index = find(data, nodeList);
		if (index == -1) {
			cout << -1 << endl;
			return;
		}
		node* curNode = nodeList[index];
		
		node* parent = curNode->parent;
		for (int i = 0; i < curNode->childs.size(); i++) {
			parent->childs.push_back(curNode->childs[i]);
			curNode->childs[i]->parent = parent;
		}
		parent->childs.erase(parent->childs.begin() + find(data, parent->childs));
		delete curNode;
		nodeList.erase(nodeList.begin() + index);
	}
	void parent(int data) {
		int index = find(data, nodeList);
		if (index == -1) {
			cout << -1 << endl;
			return;
		}
		node* parent = nodeList[index]->parent;

		if (parent == NULL)
			return;

		cout << parent->data << endl;
	}
	void child(int data) {
		int index = find(data, nodeList);
		if (index == -1) {
			cout << -1 << endl;
			return;
		}
		vector<node*> child = nodeList[index]->childs;

		if (child.size() == 0) {
			cout << -1 << endl;
			return;
		}

		for (int i = 0; i < child.size(); i++) {
			cout << child[i]->data << " ";
		}
		cout << endl;
	}
	void maxChild(int data) {
		int index = find(data, nodeList);
		if (index == -1) {
			cout << -1 << endl;
			return;
		}
		vector<node*> child = nodeList[index]->childs;

		if (child.size() == 0) {
			cout << -1 << endl;
			return;
		}

		int max = child[0]->data;
		for (int i = 1; i < child.size(); i++) {
			max < child[i]->data ? max = child[i]->data : max = max;
		}
		cout << max << endl;
	}
private:
	node* root;
	vector<node*> nodeList;
	int find(int data, vector<node*>& list) {
		for (int i = 0; i < list.size(); i++) {
			if (list[i]->data == data)
				return i;
		}
		return -1;
	}
};

int main() {
	int t;
	cin >> t;
	Tree tree = Tree();
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "insert") {
			int x, y;
			cin >> x >> y;
			tree.insert(x, y);
		}
		else if (command == "delete") {
			int x;
			cin >> x;
			tree.remove(x);
		}
		else if (command == "parent") {
			int x;
			cin >> x;
			tree.parent(x);
		}
		else if (command == "child") {
			int x;
			cin >> x;
			tree.child(x);
		}
		else if (command == "maxChild") {
			int x;
			cin >> x;
			tree.maxChild(x);
		}
	}
}