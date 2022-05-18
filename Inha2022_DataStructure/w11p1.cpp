#include <iostream>
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
	}
	void remove(int key) {
		node* deleteNode = search(root, key);
		
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
	int treeNum(node* curNode) {
		if (curNode == NULL)
			return 0;

		return treeNum(curNode->left) + treeNum(curNode->right) + 1;
	}
	int subtreeNum(int key) {
		node* curNode = search(root, key);
		return treeNum(curNode->left);
	}
private:
	node* root;
};

int main() {
	int n, m;
	cin >> n >> m;
	BST bst = BST();
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		bst.insert(num);
	}
	for (int i = 0; i < m; i++) {
		int num;
		cin >> num;
		cout << bst.subtreeNum(num) << endl;
	}
}