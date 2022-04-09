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
	void ancestor(int data, int depth) {
		int index = find(data, nodeList);
		if (index == -1) {
			return;
		}
		node* curNode = nodeList[index];
		if (curNode == root) {
			cout << depth << endl;
			return;
		}

		node* parent = curNode->parent;
		ancestor(parent->data, ++depth);
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
	int n, m;
	cin >> n >> m;
	Tree tree = Tree();
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		cin >> x >> y;
		tree.insert(x, y);
	}
	for (int i = 0; i < m; i++) {
		int v;
		cin >> v;
		tree.ancestor(v, 0);
	}
}