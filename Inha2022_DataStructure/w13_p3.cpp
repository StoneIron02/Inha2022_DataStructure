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
	vertex* src;
	vertex* dst;
	edge* prev;
	edge* next;
	edge() {
		src = dst = NULL;
		prev = next = NULL;
	}
	edge(vertex* src, vertex* dst) {
		this->src = src;
		this->dst = dst;
		prev = next = NULL;
	}
};

class vertexList {
public:
	vertexList() {
		header = trailer = new vertex();
		header->next = trailer;
		trailer->prev = header;
	}
	void insertVertex(vertex* v) {
		v->prev = trailer->prev;
		v->next = trailer;
		v->matrixId = trailer->prev->matrixId + 1;
		trailer->prev->next = v;
		trailer->prev = v;
	}
	void eraseVertex(vertex* v) {
		for (vertex* cur = v; cur != trailer; cur = cur->next)
			cur->matrixId--;
		v->prev->next = v->next;
		v->next->prev = v->prev;
		delete v;
	}
	vertex* findVertex(int id) {
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

class edgeList {
public:
	edgeList() {
		header = trailer = new edge();
		header->next = trailer;
		trailer->prev = header;
	}
	void insertEdge(edge* e) {
		e->prev = trailer->prev;
		e->next = trailer;
		trailer->prev->next = e;
		trailer->prev = e;
	}
	void eraseEdge(edge* e) {
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
		vList.insertVertex(v);
	}
	void insertEdge(int srcId, int dstId) {
		vertex* src = vList.findVertex(srcId);
		vertex* dst = vList.findVertex(dstId);

		if (matrix[src->matrixId][dst->matrixId] != NULL) {
			cout << "Exist" << endl;
			return;
		}

		edge* e = new edge(src, dst);
		eList.insertEdge(e);
		matrix[src->matrixId][dst->matrixId] = e;
		matrix[dst->matrixId][src->matrixId] = e;
	}
	void eraseEdge(int srcId, int dstId) {
		vertex* src = vList.findVertex(srcId);
		vertex* dst = vList.findVertex(dstId);

		if (matrix[src->matrixId][dst->matrixId] == NULL) {
			cout << "None" << endl;
			return;
		}

		edge* e = matrix[src->matrixId][dst->matrixId];
		eList.eraseEdge(e);
		matrix[src->matrixId][dst->matrixId] = NULL;
		matrix[dst->matrixId][src->matrixId] = NULL;
	}
	void sumAdjacentNode(int id) {
		vertex* v = vList.findVertex(id);
		bool exist = false;
		int sum = 0;
		for (int i = 0; i < matrix[v->matrixId].size(); i++) {
			if (matrix[v->matrixId][i] != NULL) {
				exist = true;
				if (matrix[v->matrixId][i]->src == v) {
					sum += matrix[v->matrixId][i]->dst->id;
				}
				else {
					sum += matrix[v->matrixId][i]->src->id;
				}
			}
		}
		if (!exist) {
			cout << "None" << endl;
			return;
		}
		cout << sum << endl;
		return;
	}
private:
	vertexList vList;
	edgeList eList;
	vector<vector<edge*>> matrix;
};

int main() {
	int t, n;
	cin >> t >> n;
	Graph graph = Graph();
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		graph.insertVertex(k);
	}
	for (int i = 0; i < t; i++) {
		string command;
		cin >> command;
		if (command == "insertEdge") {
			int s, d;
			cin >> s >> d;
			graph.insertEdge(s, d);
		}
		if (command == "eraseEdge") {
			int s, d;
			cin >> s >> d;
			graph.eraseEdge(s, d);
		}
		if (command == "SumAdjacentNode") {
			int s;
			cin >> s;
			graph.sumAdjacentNode(s);
		}
	}
}