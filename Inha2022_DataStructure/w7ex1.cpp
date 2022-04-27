#include <Iostream>
#include <vector>
using namespace std;

typedef char type;
struct node {
	type data;
	node* parent;
	vector<node*> childs;
	node(type data, node* parent) {
		this->data = data;
		this->parent = parent;
	}
};

class Tree {
public:
	Tree(type data) {
		root = new node(data, NULL);
		nodes.push_back(root);
	}
	void insert(type parentData, type data) {
		if (find(data, nodes) != -1) { // already exist
			return;
		}
		int parentIndex = find(parentData, nodes);
		if (parentIndex == -1) { // not found
			return;
		}

		node* parentNode = nodes[parentIndex];
		node* newNode = new node(data, parentNode);
		parentNode->childs.push_back(newNode);
		nodes.push_back(newNode);
	}
	void preOrder(node* curNode) {
		cout << curNode->data << " ";
		for (int i = 0; i < curNode->childs.size(); i++) {
			preOrder(curNode->childs[i]);
		}
	}
	void postOrder(node* curNode) {
		for (int i = 0; i < curNode->childs.size(); i++) {
			postOrder(curNode->childs[i]);
		}
		cout << curNode->data << " ";
	}
	node* getRoot() {
		return root;
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
	Tree tree = Tree('A');
	tree.insert('A', 'B');
	tree.insert('A', 'C');
	tree.insert('A', 'D');
	tree.insert('B', 'E');
	tree.preOrder(tree.getRoot());
	cout << endl;
	tree.postOrder(tree.getRoot());
	cout << endl;
}