#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct vertex {
	int id;
	int matrixId;
	vertex* prev;
	vertex* next;
	
	vertex() {
		id = matrixId = -1;
		prev = next = NULL;
	}
	vertex(int id) {
		this->id = id;
		matrixId = -1;
		prev = next = NULL;
	}
};

struct edge {
	vertex* source;
	vertex* destination;
	edge* prev;
	edge* next;

	edge() {
		source = destination = NULL;
		prev = next = NULL;
	}
	edge(vertex* source, vertex* destination) {
		this->source = source;
		this->destination = destination;
		prev = next = NULL;
	}
	vertex* opposite(vertex* v) {
		if (v->id == source->id)
			return destination;
		else if (v->id == destination->id)
			return source;
		else
			return NULL; // NotFound
	}
};

class VertexList {
public:
	VertexList() {
		header = trailer = new vertex();
		header->next = trailer;
		trailer->prev = header;
	}
	void insert(vertex* v) {
		v->prev = trailer->prev;
		v->next = trailer;
		v->matrixId = trailer->prev->matrixId + 1;
		trailer->prev->next = v;
		trailer->prev = v;
	}
	void erase(vertex* v) {
		for (vertex* cur = v; cur != trailer; cur = cur->next) {
			cur->matrixId--;
		}
		v->prev->next = v->next;
		v->next->prev = v->prev;
		delete v;
	}
	vertex* find(int id) {
		for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
			if (cur->id == id)
				return cur;
		}
		return NULL;
	}
private:
	vertex* header;
	vertex* trailer;
};

class EdgeList {
public:
	EdgeList() {
		header = trailer = new edge();
		header->next = trailer;
		trailer->prev = header;
	}
	void insert(edge* e) {
		e->prev = trailer->prev;
		e->next = trailer;
		trailer->prev->next = e;
		trailer->prev = e;
	}
	void erase(edge* e) {
		e->prev->next = e->next;
		e->next->prev = e->prev;
		delete e;
	}
private:
	edge* header;
	edge* trailer;
};

class Graph {
public:
	void insertVertex(int id) {
		vertex* v = new vertex(id);
		for (int i = 0; i < matrix.size(); i++) {
			matrix[i].push_back(NULL);
		}
		matrix.push_back(vector<edge*>(matrix.size() + 1, NULL));
		vList.insert(v);
	}
	void insertEdge(int sId, int dId) {
		vertex* source = vList.find(sId);
		vertex* destination = vList.find(dId);
		int sMatrixId = source->matrixId;
		int dMatrixId = destination->matrixId;
		if (matrix[sMatrixId][dMatrixId] != NULL || matrix[dMatrixId][sMatrixId] != NULL) {
			cout << "Exist" << endl;
			return;
		}

		edge* e = new edge(source, destination);
		eList.insert(e);
		matrix[sMatrixId][dMatrixId] = matrix[dMatrixId][sMatrixId] = e;
	}
	void eraseEdge(int sId, int dId) {
		vertex* source = vList.find(sId);
		vertex* destination = vList.find(dId);
		int sMatrixId = source->matrixId;
		int dMatrixId = destination->matrixId;
		if (matrix[sMatrixId][dMatrixId] == NULL || matrix[dMatrixId][sMatrixId] == NULL) {
			cout << "None" << endl;
			return;
		}

		edge* e = matrix[sMatrixId][dMatrixId];
		eList.erase(e);
		matrix[sMatrixId][dMatrixId] = matrix[dMatrixId][sMatrixId] = NULL;
	}
	bool isAdjacentTo(int sMID, int dMID) {
		return matrix[sMID][dMID] != NULL;
	}
	int maxAdjacentNode(int id) {
		vertex* v = vList.find(id);
		int MID = v->matrixId;

		int max = -1;
		for (int i = 0; i < matrix[MID].size(); i++) {
			if (matrix[MID][i] != NULL) {
				vertex* opposite = matrix[MID][i]->opposite(v);
				max < opposite->id ? max = opposite->id : max = max;
			}
		}
		return max;
	}
private:
	vector<vector<edge*>> matrix;
	VertexList vList;
	EdgeList eList;
};

int main() {
	int t, n;
	cin >> t >> n;
	Graph graph = Graph();
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		graph.insertVertex(num);
	}
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "insertEdge") {
			int a, b;
			cin >> a >> b;
			graph.insertEdge(a, b);
		}
		if (command == "eraseEdge") {
			int a, b;
			cin >> a >> b;
			graph.eraseEdge(a, b);
		}
		if (command == "MaxAdjacentNode") {
			int a;
			cin >> a;
			int max = graph.maxAdjacentNode(a);
			if (max == -1)
				cout << "None" << endl;
			else
				cout << max << endl;
		}
	}
}