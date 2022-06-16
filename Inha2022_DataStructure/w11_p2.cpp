#include <iostream>
#include <string>
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
			cout << depth(root, 0) << endl;
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
		cout << depth(curNode, 0) << endl;
	}
	void remove(int key) {
		node* curNode = find(root, key);
		cout << depth(curNode, 0) << endl;
		node* deleteNode = curNode;
		node* childNode;
		if (curNode->left == NULL && curNode->right == NULL) {
			childNode = NULL;
		}
		else if (curNode->left != NULL && curNode->right == NULL) {
			childNode = curNode->left;
		}
		else if (curNode->left == NULL && curNode->right != NULL) {
			childNode = curNode->right;
		}
		else {
			deleteNode = deleteNode->right;
			while (deleteNode->left != NULL) {
				deleteNode = deleteNode->left;
			}
			curNode->key = deleteNode->key;
			childNode = deleteNode->right;
		}

		node* parentNode = deleteNode->parent;
		if (parentNode == NULL) {
			root = childNode;
			if (childNode != NULL)
				childNode->parent = NULL;
		}
		else if (deleteNode == parentNode->left) {
			parentNode->left = childNode;
			if (childNode != NULL)
				childNode->parent = parentNode;
		}
		else if (deleteNode == parentNode->right) {
			parentNode->right = childNode;
			if (childNode != NULL)
				childNode->parent = parentNode;
		}
		delete deleteNode;
	}
	int treeSize(node* curNode) {
		if (curNode == NULL)
			return 0;
		return treeSize(curNode->left) + treeSize(curNode->right) + 1;
	}
	int treeSize(int x) {
		node* curNode = find(root, x);
		return treeSize(curNode->right);
	}
	int depth(node* curNode, int n) {
		if (curNode == root)
			return n;
		return depth(curNode->parent, n + 1);
	}
	int height(node* curNode) {
		if (curNode == NULL)
			return 0;
		int leftH = height(curNode->left);
		int rightH = height(curNode->right);
		return leftH > rightH ? 1 + leftH : 1 + rightH;
	}
	int height(int x) {
		node* curNode = find(root, x);
		return height(curNode) - 1;
	}
	int min(node* curNode, int k) {
		int n = 1;
		if (curNode->left != NULL)
			n += treeSize(curNode->left);

		if (k < n) {
			return min(curNode->left, k);
		}
		else if (k > n) {
			return min(curNode->right, k - n);
		}
		else {
			return curNode->key;
		}
	}
	int min(int k) {
		return min(root, k);
	}
private:
	node* root;
};

int main() {
	int t;
	cin >> t;
	BST bst = BST();
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "insert") {
			int x;
			cin >> x;
			bst.insert(x);
		}
		else if (command == "delete") {
			int x;
			cin >> x;
			bst.remove(x);
		}
		else if (command == "min") {
			int k;
			cin >> k;
			cout << bst.min(k) << endl;
		}
		else if (command == "height") {
			int x;
			cin >> x;
			cout << bst.height(x) << endl;
		}
	}
}