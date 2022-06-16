#include <iostream>
using namespace std;

struct node {
	int key;
	node* left;
	node* right;
	node* parent;
	node(int key) {
		this->key = key;
		left = right = parent = NULL;
	}
};

class BST {
public:
	node* find(node* curNode, int key) {
		if (curNode == NULL)
			return NULL;
		if (key < curNode->key)
			return find(curNode->left, key);
		else if (key > curNode->key)
			return find(curNode->right, key);
		else
			return curNode;
	}
	void insert(int key) {
		node* newNode = new node(key);
		if (root == NULL) {
			root = newNode;
			return;
		}

		node* curNode = root;
		node* parentNode = NULL;
		while (curNode != NULL) {
			parentNode = curNode;
			if (key < curNode->key)
				curNode = curNode->left;
			else
				curNode = curNode->right;
		}
		curNode = newNode;
		curNode->parent = parentNode;
		if (key < parentNode->key)
			parentNode->left = curNode;
		else
			parentNode->right = curNode;
	}
	int treeSize(node* curNode) {
		if (curNode == NULL)
			return 0;
		return treeSize(curNode->left) + treeSize(curNode->right) + 1;
	}
	int treeSize(int x) {
		node* curNode = find(root, x);
		return treeSize(curNode->left);
	}
private:
	node* root;
};

int main() {
	int n, m;
	cin >> n >> m;
	BST bst = BST();
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		bst.insert(x);
	}
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		cout << bst.treeSize(x) << endl;
	}
}