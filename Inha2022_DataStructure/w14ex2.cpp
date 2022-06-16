#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct edge;
struct edgeNode;
struct EdgeList {
	edgeNode* header;
	edgeNode* trailer;
	EdgeList();
	void insertEdge(edge* e);
	void eraseEdge(edgeNode* e);
};

struct vertex {
	int id;
	int degree;
	bool visit;
	vertex* prev;
	vertex* next;
	EdgeList incidents;
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
	edgeNode* sIncidentEdge;
	edgeNode* dIncidentEdge;
	edgeNode* totalEdge;
	edge() {
		source = destination = NULL;
	}
	edge(vertex* source, vertex* destination) {
		this->source = source;
		this->destination = destination;
	}
};

struct edgeNode {
	edge* edgeInfo;
	edgeNode* prev;
	edgeNode* next;
	edgeNode() {
		edgeInfo = NULL;
		prev = next = NULL;
	}
	edgeNode(edge* edgeInfo) {
		this->edgeInfo = edgeInfo;
		prev = next = NULL;
	}
};

class VertexList {
public:
	VertexList() {
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
private:
	vertex* header;
	vertex* trailer;
};

EdgeList::EdgeList() {
	header = trailer = new edgeNode();
	header->next = trailer;
	trailer->prev = header;
}
void EdgeList::insertEdge(edge* e) {
	edgeNode* eNode = new edgeNode(e);
	eNode->prev = trailer->prev;
	eNode->next = trailer;
	trailer->prev->next = eNode;
	trailer->prev = eNode;
}
void EdgeList::eraseEdge(edgeNode* eNode) {
	eNode->prev->next = eNode->next;
	eNode->next->prev = eNode->prev;
	delete eNode;
}

class Graph {
public:
	edge* findEdge(vertex* source, vertex* destination) {
		if (source->degree < destination->degree) {
			for (edgeNode* cur = source->incidents.header->next; cur != source->incidents.trailer; cur = cur->next) {
				if (cur->edgeInfo->destination == destination)
					return cur->edgeInfo;
			}
		}
		else {
			for (edgeNode* cur = destination->incidents.header->next; cur != destination->incidents.trailer; cur = cur->next) {
				if (cur->edgeInfo->source == source)
					return cur->edgeInfo;
			}
		}
		return NULL;
	}
	void insertVertex(int id) {
		if (vList.findVertex(id) != NULL) {
			// ElreadyExist
			return;
		}

		vertex* v = new vertex(id);
		vList.insertVertex(v);
	}
	void eraseVertex(int id) {
		vertex* v = vList.findVertex(id);
		if (v == NULL) {
			// NotFound
			return;
		}

		for (edgeNode* cur = v->incidents.header->next; cur != v->incidents.trailer; cur = cur->next) {
			eList.eraseEdge(cur->edgeInfo->totalEdge);
			if (cur == cur->edgeInfo->sIncidentEdge)
				cur->edgeInfo->destination->incidents.eraseEdge(cur->edgeInfo->dIncidentEdge);
			else
				cur->edgeInfo->source->incidents.eraseEdge(cur->edgeInfo->sIncidentEdge);
			delete cur->edgeInfo;
		}
		vList.eraseVertex(v);
	}
	void insertEdge(int sourceId, int destinationId) {
		vertex* source = vList.findVertex(sourceId);
		vertex* destination = vList.findVertex(destinationId);
		if (source == NULL || destination == NULL) {
			// NotFound
			return;
		}
		if (findEdge(source, destination) != NULL) {
			// NotFound
			return;
		}

		edge* e = new edge(source, destination);
		source->incidents.insertEdge(e);
		destination->incidents.insertEdge(e);
		eList.insertEdge(e);
		e->sIncidentEdge = source->incidents.trailer->prev;
		e->dIncidentEdge = destination->incidents.trailer->prev;
		e->totalEdge = eList.trailer->prev;
		source->degree++;
		destination->degree++;
	}
	void eraseEdge(int sourceId, int destinationId) {
		vertex* source = vList.findVertex(sourceId);
		vertex* destination = vList.findVertex(destinationId);
		if (source == NULL || destination == NULL) {
			// NotFound
			return;
		}
		edge* e = findEdge(source, destination);
		if (e != NULL) {
			// NotFound
			return;
		}

		source->incidents.eraseEdge(e->sIncidentEdge);
		destination->incidents.eraseEdge(e->dIncidentEdge);
		eList.eraseEdge(e->totalEdge);
		source->degree--;
		destination->degree--;
		delete e;
	}
	void DFS(vertex* cur) {
		cur->visit = true;
		for (edgeNode* e = cur->incidents.header->next; e != cur->incidents.trailer; e = e->next) {
			if (cur == e->edgeInfo->source) {
				if (e->edgeInfo->destination->visit != true)
					DFS(e->edgeInfo->destination);
			}
			else {
				if (e->edgeInfo->source->visit != true)
					DFS(e->edgeInfo->source);
			}
		}
	}
	void BFS(int vertexId) {
		vertex* v = vList.findVertex(vertexId);
		queue<vertex*> q;
		q.push(v);
		v->visit = true;
		while (!q.empty()) {
			vertex* cur = q.front();
			q.pop();
			for (edgeNode* e = cur->incidents.header->next; e != cur->incidents.trailer; e = e->next) {
				if (cur == e->edgeInfo->source) {
					if (e->edgeInfo->destination->visit != true) {
						e->edgeInfo->destination->visit = true;
						q.push(e->edgeInfo->destination);
					}
				}
				else {
					if (e->edgeInfo->source->visit != true) {
						e->edgeInfo->source->visit = true;
						q.push(e->edgeInfo->source);
					}
				}
			}
		}
	}
private:
	VertexList vList;
	EdgeList eList;
};

int main() {

}