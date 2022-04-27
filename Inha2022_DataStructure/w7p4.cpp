#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node {
	int data;
	int size;
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
	void setSize(int data, int size) {
		int curIndex = find(data, nodes);
		node* curNode = nodes[curIndex];
		curNode->size = size;
	}
	int postOrder(node* curNode) {
		int totalSize = 0;
		for (int i = 0; i < curNode->childs.size(); i++) {
			totalSize += postOrder(curNode->childs[i]);
		}
		totalSize += curNode->size;
		return totalSize;
	}
	void getSize(int x) {
		cout << postOrder(nodes[find(x, nodes)]) << endl;
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
	int count;
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
	for (int i = 0; i < n; i++) {
		int x, w;
		cin >> x >> w;
		tree.setSize(x, w);
	}
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		tree.getSize(x);
	}
}