#include <iostream>
#include <vector>
#include <string>
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
		nodes.push_back(root);
	}
	void insert(int parentData, int data) {
		if (find(data, nodes) != -1)
			return;
		int parentIndex = find(parentData, nodes);
		if (parentIndex == -1)
			return;

		node* parentNode = nodes[parentIndex];
		node* newNode = new node(data, parentNode);
		parentNode->childs.push_back(newNode);
		nodes.push_back(newNode);
	}
	void postOrder(node* curNode, int depth) {
		for (int i = 0; i < curNode->childs.size(); i++) {
			postOrder(curNode->childs[i], depth + 1);
		}
		cout << depth << " ";
	}
	void printDepth() {
		postOrder(root, 0);
	}
private:
	node* root;
	vector<node*> nodes;
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
	for (int i = 0; i < t; i++) {
		Tree tree = Tree();
		int n;
		cin >> n;
		for (int j = 0; j < n - 1; j++) {
			int x, y;
			cin >> x >> y;
			tree.insert(x, y);
		}
		tree.printDepth();
	}

}