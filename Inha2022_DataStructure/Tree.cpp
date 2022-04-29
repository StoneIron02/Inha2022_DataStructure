#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef int type;
struct node {
	type data;
	node* parent;
	vector<node*> childs;
	node(type data, node* parent) {
		this->data = data;
		this->parent = parent;
	}
};

class Tree {
public:
	Tree() {
		root = new node(1, NULL);
		nodes.push_back(root);
	}
	int size() {
		return nodes.size();
	}
	bool empty() {
		return (size() == 0);
	}
	bool isRoot(node* node) {
		return (node == root);
	}
	bool isExternal(node* node) {
		return (node->childs.size() == 0);
	}
	void parent(type data) {
		int index = find(data, nodes);
		if (index == -1) {
			// NotFornd
			return;
		}
		node* parent = nodes[index]->parent;
		if (parent == NULL) { //
			return;
		}
		cout << parent->data << endl;
	}
	void children(type data) {
		int index = find(data, nodes);
		if (index == -1) {
			// NotFornd
			return;
		}
		vector<node*>& childs = nodes[index]->childs;
		for (int i = 0; i < childs.size(); i++) {
			cout << childs[i]->data << " ";
		}
		cout << endl;
	}
	node* getRoot() {
		return root;
	}
	vector<node*>& positions() {
		return nodes;
	}
	void insert(type parentData, type data) {
		if (find(data, nodes) != -1) {
			// AlreadyExist
			return;
		}
		int parentIndex = find(parentData, nodes);
		if (parentIndex == -1) {
			// ParentNotFound
			return;
		}
		node* parentNode = nodes[parentIndex];
		node* newNode = new node(data, parentNode);
		parentNode->childs.push_back(newNode);
		nodes.push_back(newNode);
	}
	void remove(type data) {
		int index = find(data, nodes);
		if (index == -1) {
			// NotFound
			return;
		}
		node* curNode = nodes[index];
		if (curNode == root) { //
			// RootCanNotRemove
			return;
		}

		node* parentNode = curNode->parent;
		for (int i = 0; i < curNode->childs.size(); i++) { //
			parentNode->childs.push_back(curNode->childs[i]);
			curNode->childs[i]->parent = parentNode;
		}
		parentNode->childs.erase(parentNode->childs.begin() + find(data, parentNode->childs));
		delete curNode; //
		nodes.erase(nodes.begin() + index);
	}
	void preOrder(node* node) {
		cout << node->data << " ";
		for (int i = 0; i < node->childs.size(); i++) {
			preOrder(node->childs[i]);
		}
	}
	void postOrder(node* node) {
		for (int i = 0; i < node->childs.size(); i++) {
			postOrder(node->childs[i]);
		}
		cout << node->data << " ";
	}
private:
	node* root;
	vector<node*> nodes;
	int find(type data, vector<node*>& list) {
		for (int i = 0; i < list.size(); i++) {
			if (list[i]->data == data) {
				return i;
			}
		}
		return -1;
	}
};

int main() {
	Tree tree = Tree();
	while (true) {
		string command;
		cin >> command;
		if (command == "size") {
			cout << tree.size() << endl;
		}
		else if (command == "empty") {
			cout << tree.empty() << endl;
		}
		else if (command == "parent") {
			int x;
			cin >> x;
			tree.parent(x);
		}
		else if (command == "children") {
			int x;
			cin >> x;
			tree.children(x);
		}
		else if (command == "insert") {
			int x, y;
			cin >> x >> y;
			tree.insert(x, y);
		}
		else if (command == "remove") {
			int x;
			cin >> x;
			tree.remove(x);
		}
		else if (command == "preOrder") {
			tree.preOrder(tree.getRoot());
			cout << endl;
		}
		else if (command == "postOrder") {
			tree.postOrder(tree.getRoot());
			cout << endl;
		}
	}
}