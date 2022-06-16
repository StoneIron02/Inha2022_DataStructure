#include <iostream>
#include <string>
using namespace std;

typedef int type;
struct node {
	type key;
	node* parent;
	node* left;
	node* right;
	node(type key) {
		this->key = key;
		parent = left = right = NULL;
	}
};

class BST {
public:
	BST() {
		root = NULL;
	}
	node* search(node* curNode, type key) {
		if (curNode == NULL)
			return NULL;

		if (key < curNode->key)
			return search(curNode->left, key);
		else if (key > curNode->key)
			return search(curNode->right, key);
		else
			return curNode;
	}
	void insert(type key) {
		if (search(root, key) != NULL) {
			// AlreadyExist
			return;
		}

		node* newNode = new node(key);
		if (root == NULL) {
			root = newNode;
		}
		else {
			node* curNode = root;
			node* parentNode = NULL;
			while (curNode != NULL) {
				parentNode = curNode;
				if (key < curNode->key)
					curNode = curNode->left;
				else
					curNode = curNode->right;
			}

			newNode->parent = parentNode;
			if (key < parentNode->key)
				parentNode->left = newNode;
			else
				parentNode->right = newNode;
		}
	}
	void remove(type key) {
		node* deleteNode = search(root, key);
		if (deleteNode == NULL) {
			// NotFound
			return;
		}

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

	int subtreeNum(type key) {
		node* curNode = search(root, key);
		return subtreeNum(curNode->left);
	}
	int subtreeNum(node* curNode) {
		if (curNode == NULL)
			return 0;
		return subtreeNum(curNode->left) + subtreeNum(curNode->right) + 1;
	}

	type max(int k) {
		node* maxNode = max(root, k);
		return maxNode->key;
	}
	node* max(node* curNode, int k) {
		int n = 1;
		if (curNode->right != NULL)
			n += subtreeNum(curNode->right);

		if (k == n)
			return curNode;
		else if (k < n)
			return max(curNode->right, k);
		else
			return max(curNode->left, k - n);
	}
	type min(int k) {
		node* minNode = min(root, k);
		return minNode->key;
	}
	node* min(node* curNode, int k) {
		int n = 1;
		if (curNode->left != NULL)
			n += subtreeNum(curNode->left);

		if (k == n)
			return curNode;
		else if (k < n)
			return min(curNode->left, k);
		else
			return min(curNode->right, k - n);
	}

	int height(type key) {
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
	BST bst = BST();
	while (true) {
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
		else if (command == "subtreeNum") {
			int n;
			cin >> n;
			cout << bst.subtreeNum(n) << endl;
		}
		else if (command == "max") {
			int n;
			cin >> n;
			cout << bst.max(n) << endl;
		}
		else if (command == "min") {
			int n;
			cin >> n;
			cout << bst.min(n) << endl;
		}
		else if (command == "height") {
			int n;
			cin >> n;
			cout << bst.height(n) << endl;
		}
	}
}