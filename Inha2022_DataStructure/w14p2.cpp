#include <iostream>
#include <vector>
using namespace std;

struct edge;
struct edgeNode;
class edgeList {
public:
	edgeNode* header;
	edgeNode* trailer;
	edgeList();
	void insert(edge* e);
	void erase(edgeNode* eNode);
};

struct vertex {
	int id;
	int degree;
	bool visit;
	vertex* prev;
	vertex* next;
	edgeList incidents;
	vertex() {
		id = -1;
		degree = 0;
		prev = next = NULL;
		visit = false;
	}
	vertex(int id) {
		this->id = id;
		degree = 0;
		prev = next = NULL;
		visit = false;
	}
};

struct edge {
	vertex* source;
	vertex* destination;
	edgeNode* sIncident;
	edgeNode* dIncident;
	edgeNode* totalNode;
	edge() {
		source = destination = NULL;
	}
	edge(vertex* source, vertex* destination) {
		this->source = source;
		this->destination = destination;
	}
};

struct edgeNode {
	edge* e;
	edgeNode* prev;
	edgeNode* next;
	edgeNode() {
		prev = next = NULL;
	}
	edgeNode(edge* e) {
		this->e = e;
		prev = next = NULL;
	}
};

class vertexList {
public:
	vertexList() {
		trailer = header = new vertex();
		header->next = trailer;
		trailer->prev = header;
	}
	void insert(vertex* v) {
		v->prev = trailer->prev;
		v->next = trailer;
		trailer->prev->next = v;
		trailer->prev = v;
	}
	void erase(vertex* v) {
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
	void reset() {
		for (vertex* v = header->next; v != trailer; v = v->next) {
			v->visit = false;
		}
	}
private:
	vertex* trailer;
	vertex* header;
};

edgeList::edgeList() {
	header = trailer = new edgeNode();
	header->next = trailer;
	trailer->prev = header;
}
void edgeList::insert(edge* e) {
	edgeNode* eNode = new edgeNode(e);
	eNode->prev = trailer->prev;
	eNode->next = trailer;
	trailer->prev->next = eNode;
	trailer->prev = eNode;
}
void edgeList::erase(edgeNode* eNode) {
	eNode->prev->next = eNode->next;
	eNode->next->prev = eNode->prev;
	delete eNode;
}

class Graph {
public:
	void insertVertex(int id) {
		vertex* v = new vertex(id);
		vList.insert(v);
	}
	void insertEdge(int sId, int dId) {
		vertex* s = vList.find(sId);
		vertex* d = vList.find(dId);
		edge* e = new edge(s, d);
		s->incidents.insert(e);
		d->incidents.insert(e);
		eList.insert(e);
		e->sIncident = s->incidents.trailer->prev;
		e->dIncident = d->incidents.trailer->prev;
		e->totalNode = eList.trailer->prev;
		s->degree++;
		d->degree++;
	}
	void DFS(vertex* cur) {
		cur->visit = true;
		if (cur->id < min)
			min = cur->id;
		for (edgeNode* e = cur->incidents.header->next; e != cur->incidents.trailer; e = e->next) {
			if (cur == e->e->source) {
				if (e->e->destination->visit != true)
					DFS(e->e->destination);
			}
			else {
				if (e->e->source->visit != true)
					DFS(e->e->source);
			}
		}
	}
	void DFS(int c, int n) {
		vList.reset();
		min = n;
		DFS(vList.find(c));
		cout << min << endl;
	}
private:
	int min;
	vertexList vList;
	edgeList eList;
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n, m, k;
		cin >> n >> m >> k;
		Graph graph = Graph();
		for (int j = 1; j <= n; j++) {
			graph.insertVertex(j);
		}
		for (int j = 0; j < m; j++) {
			int a, b;
			cin >> a >> b;
			graph.insertEdge(a, b);
		}
		for (int j = 0; j < k; j++) {
			int c;
			cin >> c;
			graph.DFS(c, n);
		}
	}
}