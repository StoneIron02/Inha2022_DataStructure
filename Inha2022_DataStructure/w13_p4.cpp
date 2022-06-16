#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define NOTHING 0
#define FRIEND 1
#define PEER 2

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
	int w;
	edge() {
		src = dst = NULL;
		prev = next = NULL;
		w = 0;
	}
	edge(vertex* src, vertex* dst, int w) {
		this->src = src;
		this->dst = dst;
		prev = next = NULL;
		this->w = w;
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
	void insertEdge(int srcId, int dstId, int w) {
		vertex* src = vList.findVertex(srcId);
		vertex* dst = vList.findVertex(dstId);

		edge* e = new edge(src, dst, w);
		eList.insertEdge(e);
		matrix[src->matrixId][dst->matrixId] = e;
	}
	void recommend(int k, int f) {
		vertex* v = vList.findVertex(k);
		if (f == 0) f = 2;

		vector<int> friends;
		vector<int> peers;
		for (int i = 0; i < matrix[v->matrixId].size(); i++) {
			if (matrix[v->matrixId][i]->w == FRIEND) {
				friends.push_back(matrix[v->matrixId][i]->dst->matrixId);
			}
			if (matrix[v->matrixId][i]->w == PEER) {
				peers.push_back(matrix[v->matrixId][i]->dst->matrixId);
			}
		}

		vector<int> results;
		for (int i = 0; i < peers.size(); i++) {
			for (int j = 0; j < matrix.size(); j++) {
				if (j == v->matrixId) continue;
				if (matrix[peers[i]][j]->w == f) {
					if (matrix[v->matrixId][j]->w == NOTHING) {
						push(results, matrix[peers[i]][j]->dst->id);
					}
				}
			}
		}

		if (results.size() == 0) {
			cout << 0 << endl;
			return;
		}
		for (int i = 0; i < results.size(); i++) {
			cout << results[i] << " ";
		}
		cout << endl;
	}
	void push(vector<int>& results, int n) {
		for (int i = 0; i < results.size(); i++) {
			if (n < results[i]) {
				results.insert(results.begin() + i, n);
				return;
			}
			if (n == results[i]) {
				return;
			}
		}
		results.push_back(n);
	}
private:
	vertexList vList;
	edgeList eList;
	vector<vector<edge*>> matrix;
};

int main() {
	int n, m;
	cin >> n >> m;
	Graph graph = Graph();
	for (int i = 1; i <= n; i++) {
		graph.insertVertex(i);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int w;
			cin >> w;
			graph.insertEdge(i, j, w);
		}
	}
	for (int i = 0; i < m; i++) {
		int k, f;
		cin >> k >> f;
		graph.recommend(k, f);
	}
}