#include <iostream>
#include <string>
#include <vector>
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
		if (search(root, key) != NULL) {
			//AlreadyExist
			return;
		}

		node* newNode = new node(key);
		if (root == NULL)
			root = newNode;
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
		if (deleteNode == NULL) {
			//NotFound
			return;
		}
		
		node* childNode;
		if (deleteNode->left == NULL && deleteNode->right == NULL)
			childNode = NULL;
		else if (deleteNode->left == NULL && deleteNode->right != NULL)
				childNode = deleteNode->right;
		else if (deleteNode->left != NULL && deleteNode->right == NULL)
			childNode = deleteNode->left;
		else {
			childNode = deleteNode->right;
			while(childNode->left != NULL)
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
		else {
			parentNode->right = childNode;
			if (childNode != NULL)
				childNode->parent = parentNode;
		}
		delete deleteNode;
	}
private:
	node* root;
};

int main() {

}