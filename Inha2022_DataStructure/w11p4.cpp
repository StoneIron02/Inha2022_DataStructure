#include <iostream>
#include <string>
using namespace std;

struct node {
	int key;
	node* parent;
	node* left;
	node* right;
	node(int key) {
		this->key = key;
		parent = left = right = NULL;
	}
};

class BST {
public:
	BST() {
		root = NULL;
	}
	node* search(node* curNode, int key) {
		if (curNode == NULL)
			return NULL;

		if (key > curNode->key)
			return search(curNode->right, key);
		else if (key < curNode->key)
			return search(curNode->left, key);
		else
			return curNode;
	}
	void insert(int key) {
		node* newNode = new node(key);
		if (root == NULL) {
			root = newNode;
		}
		else {
			node* curNode = root;
			node* parentNode = NULL;
			while (curNode != NULL) {
				parentNode = curNode;
				if (key > curNode->key)
					curNode = curNode->right;
				else
					curNode = curNode->left;
			}

			newNode->parent = parentNode;
			if (key > parentNode->key)
				parentNode->right = newNode;
			else
				parentNode->left = newNode;
		}
		cout << getDepth(newNode, 0) << endl;
	}
	void remove(int key) {
		node* deleteNode = search(root, key);
		cout << getDepth(deleteNode, 0) << endl;

		node* childNode;
		if (deleteNode->left == NULL && deleteNode->right == NULL)
			childNode = NULL;
		else if (deleteNode->left != NULL && deleteNode->right == NULL)
			childNode = deleteNode->left;
		else if (deleteNode->left == NULL && deleteNode->right != NULL)
			childNode = deleteNode->right;
		else {
			childNode = deleteNode->right;
			while (childNode->left != NULL)
				childNode = childNode->left;
			deleteNode->key = childNode->key;
			deleteNode = childNode;
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

	int getDepth(node* curNode, int depth) {
		if (curNode == root) {
			return depth;
		}
		return getDepth(curNode->parent, depth + 1);
	}
	int treeNum(node* curNode) {
		if (curNode == NULL)
			return 0;

		return treeNum(curNode->left) + treeNum(curNode->right) + 1;
	}
	int max(int k) {
		node* maxNode = max(root, k);
		return maxNode->key;
	}
	node* max(node* curNode, int k) {
		int n = 1;
		if (curNode->right != NULL)
			n += treeNum(curNode->right);

		if (n == k)
			return curNode;
		else if (n > k)
			return max(curNode->right, k);
		else
			return max(curNode->left, k - n);
	}
	int height(int key) {
		node* curNode = search(root, key);
		return height(curNode) - 1;
	}
	int height(node* curNode) {
		if (curNode == NULL)
			return 0;

		int leftHeight = height(curNode->left);
		int rightHeight = height(curNode->right);
		return (leftHeight > rightHeight ? ++leftHeight : ++rightHeight);
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
			int n;
			cin >> n;
			bst.insert(n);
		}
		else if (command == "delete") {
			int n;
			cin >> n;
			bst.remove(n);
		}
		else if (command == "max") {
			int n;
			cin >> n;
			cout << bst.max(n) << endl;
		}
		else if (command == "height") {
			int n;
			cin >> n;
			cout << bst.height(n) << endl;
		}
	}
}