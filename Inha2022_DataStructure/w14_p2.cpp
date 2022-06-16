#include <iostream>
#include <vector>
using namespace std;

struct vertex;
struct incidentEdge;
struct edge;
struct incidentEdgeList {
	incidentEdgeList();
	void insert(edge* e);
	void erase(incidentEdge* ie);
	incidentEdge* header;
	incidentEdge* trailer;
};

struct vertex {
	int id;
	int degree;
	incidentEdgeList incidents;
	vertex* prev;
	vertex* next;
	int visited;
	vertex() {
		id = -1;
		degree = 0;
		prev = next = NULL;
		visited = false;
	}
	vertex(int id) {
		this->id = id;
		degree = 0;
		prev = next = NULL;
		visited = false;
	}
};

struct incidentEdge {
	edge* e;
	incidentEdge* prev;
	incidentEdge* next;
	incidentEdge() {
		e = NULL;
		prev = next = NULL;
	}
	incidentEdge(edge* e) {
		this->e = e;
		prev = next = NULL;
	}
};

struct edge {
	vertex* src;
	vertex* dst;
	incidentEdge* srcIncidentPoint;
	incidentEdge* dstIncidentPoint;
	edge* prev;
	edge* next;
	edge() {
		src = dst = NULL;
		srcIncidentPoint = dstIncidentPoint = NULL;
		prev = next = NULL;
	}
	edge(vertex* src, vertex* dst) {
		this->src = src;
		this->dst = dst;
		srcIncidentPoint = dstIncidentPoint = NULL;
		prev = next = NULL;
	}
	vertex* opposite(vertex* v) {
		if (v == src)
			return dst;
		else if (v == dst)
			return src;
		else
			return NULL;
	}
};

incidentEdgeList::incidentEdgeList() {
	header = trailer = new incidentEdge();
	header->next = trailer;
	trailer->prev = header;
}
void incidentEdgeList::insert(edge* e) {
	incidentEdge* ie = new incidentEdge(e);
	ie->prev = trailer->prev;
	ie->next = trailer;
	trailer->prev->next = ie;
	trailer->prev = ie;
}
void incidentEdgeList::erase(incidentEdge* ie) {
	ie->prev->next = ie->next;
	ie->next->prev = ie->prev;
	delete ie;
}

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
		trailer->prev->next = v;
		trailer->prev = v;
	}
	void eraseVertex(vertex* v) {
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
	void resetLabel() {
		for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
			cur->visited = false;
		}
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
		vList.insertVertex(v);
	}
	void insertEdge(int srcId, int dstId) {
		vertex* src = vList.findVertex(srcId);
		vertex* dst = vList.findVertex(dstId);

		edge* e = new edge(src, dst);
		eList.insertEdge(e);

		src->incidents.insert(e);
		e->srcIncidentPoint = src->incidents.trailer->prev;
		src->degree++;

		dst->incidents.insert(e);
		e->dstIncidentPoint = dst->incidents.trailer->prev;
		dst->degree++;
	}
	void DFS(vertex* v) {
		v->visited = true;
		if (min > v->id)
			min = v->id;
		for (incidentEdge* e = v->incidents.header->next; e != v->incidents.trailer; e = e->next) {
			vertex* w = e->e->opposite(v);
			if (!w->visited) {
				DFS(w);
			}
		}
	}
	void DFS(int id) {
		vList.resetLabel();
		min = id;
		vertex* v = vList.findVertex(id);
		DFS(v);
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
			graph.insertEdge(b, a);
		}
		for (int j = 0; j < k; j++) {
			int c;
			cin >> c;
			graph.DFS(c);
		}
	}
}