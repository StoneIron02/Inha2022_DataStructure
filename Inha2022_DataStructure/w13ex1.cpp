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
		v->matrixId = trailer->prev->matrixId + 1;
		trailer->prev->next = v;
		trailer->prev = v;
	}
	void eraseVertex(vertex* v) {
		for (vertex* cur = v; cur != trailer; cur = cur->next) {
			cur->matrixId--;
		}
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

class EdgeList {
public:
	EdgeList() {
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
		if (vList.findVertex(id) != NULL) {
			// AlreadyExist
			return;
		}

		vertex* v = new vertex(id);
		for (int i = 0; i < matrix.size(); i++)
			matrix[i].push_back(NULL);
		matrix.push_back(vector<edge*>(matrix.size() + 1, NULL));
		vList.insertVertex(v);
	}
	void eraseVertex(int id) {
		vertex* v = vList.findVertex(id);
		if (v == NULL) {
			// NotFound
			return;
		}

		int matrixId = v->matrixId;
		for (int i = 0; i < matrix.size(); i++) {
			if (i != matrixId) {
				if (matrix[i][matrixId] != NULL) {
					eList.eraseEdge(matrix[i][matrixId]);
				}
				matrix[i].erase(matrix[i].begin() + matrixId);
			}
		}
		matrix.erase(matrix.begin() + matrixId);
		vList.eraseVertex(v);
	}
	void insertEdge(int sourceId, int destinationId) {
		vertex* source = vList.findVertex(sourceId);
		vertex* destination = vList.findVertex(destinationId);
		if (source == NULL || destination == NULL) {
			// NotFound
			return;
		}

		int sMatrixId = source->matrixId;
		int dMatrixId = destination->matrixId;
		if (matrix[sMatrixId][dMatrixId] != NULL || matrix[dMatrixId][sMatrixId] != NULL) {
			// AlreadyExist
			return;
		}

		edge* e = new edge(source, destination);
		eList.insertEdge(e);
		matrix[sMatrixId][dMatrixId] = matrix[dMatrixId][sMatrixId] = e;
	}
	void eraseEdge(int sourceId, int destinationId) {
		vertex* source = vList.findVertex(sourceId);
		vertex* destination = vList.findVertex(destinationId);
		if (source == NULL || destination == NULL) {
			// NotFound
			return;
		}

		int sMatrixId = source->matrixId;
		int dMatrixId = destination->matrixId;
		if (matrix[sMatrixId][dMatrixId] == NULL || matrix[dMatrixId][sMatrixId] == NULL) {
			// NotFound
			return;
		}

		edge* e = matrix[sMatrixId][dMatrixId];
		eList.eraseEdge(e);
		matrix[sMatrixId][dMatrixId] = matrix[dMatrixId][sMatrixId] = NULL;
	}
private:
	vector<vector<edge*>> matrix;
	VertexList vList;
	EdgeList eList;
};

int main() {

}