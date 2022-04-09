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
	Tree(int data) {
		root = new node(1, NULL);
		nodeList.push_back(root);
	}
	void insertNode(int parentData, int data) {
		if (find(data, nodeList) != -1) {
			return;
		}

		int index = find(parentData, nodeList);
		if (index == -1) {
			return;
		}

		node* parentNode = nodeList[index];
		node* newNode = new node(data, parentNode);
		parentNode->childs.push_back(newNode);
		nodeList.push_back(newNode);
	}
	void deleteNode(int data) {
		int index = find(data, nodeList);
		if (index == -1) {
			return;
		}

		node* delNode = nodeList[index];
		if (delNode == root) {
			return;
		}

		node* parentNode = delNode->parent;
		for (int i = 0; i < delNode->childs.size(); i++) {
			parentNode->childs.push_back(delNode->childs[i]);
			delNode->childs[i]->parent = parentNode;
		}

		vector<node*>& childs = parentNode->childs;
		childs.erase(childs.begin() + find(data, childs));
		delete nodeList[index];
		nodeList.erase(nodeList.begin() + index);
	}
	void printParent(int data) {
		int index = find(data, nodeList);
		if (index == -1) {
			return;
		}

		node* curNode = nodeList[index];
		if (curNode == root) {
			return;
		}

		cout << curNode->parent->data << endl;

	}
	void printChild(int data) {
		int index = find(data, nodeList);
		if (index == -1) {
			return;
		}

		vector<node*>& childs = nodeList[index]->childs;
		for (int i = 0; i < childs.size(); i++) {
			cout << childs[i]->data << " ";
		}
		cout << endl;
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

}