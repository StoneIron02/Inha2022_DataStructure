#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef int type;
struct vertex {
	type id;
	int matrixId;
	vertex* prev;
	vertex* next;
	vertex() {
		id = matrixId = -1;
		prev = next = NULL;
	}
	vertex(type id) {
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
	vertex* findVertex(type id) {
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
	void insertVertex(type id) {
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
	bool isAdjacentTo(int sMatrixId, int dMatrixId) {
		return matrix[sMatrixId][dMatrixId] != NULL;
	}
	int maxAdjacentNode(type id) {
		vertex* v = vList.findVertex(id);
		int matrixId = v->matrixId;

		int max = -1;
		for (int i = 0; i < matrix[matrixId].size(); i++) {
			if (matrix[matrixId][i] != NULL) {
				vertex* opposite = matrix[matrixId][i]->opposite(v);
				max < opposite->id ? max = opposite->id : max = max;
			}
		}
		return max;
	}
	int sumAdjacentNode(type id) {
		vertex* v = vList.findVertex(id);
		int matrixId = v->matrixId;

		int sum = 0;
		for (int i = 0; i < matrix[matrixId].size(); i++) {
			if (matrix[matrixId][i] != NULL) {
				vertex* opposite = matrix[matrixId][i]->opposite(v);
				sum += opposite->id;
			}
		}
		return sum;
	}
private:
	vector<vector<edge*>> matrix;
	VertexList vList;
	EdgeList eList;
};

int main() {
	Graph graph = Graph();
	while (true) {
		string command;
		cin >> command;
		if (command == "insertVertex") {
			int a;
			cin >> a;
			graph.insertVertex(a);
		}
		else if (command == "eraseVertex") {
			int a;
			cin >> a;
			graph.eraseVertex(a);
		}
		else if (command == "insertEdge") {
			int a, b;
			cin >> a >> b;
			graph.insertEdge(a, b);
		}
		else if (command == "eraseEdge") {
			int a, b;
			cin >> a >> b;
			graph.eraseEdge(a, b);
		}
		else if (command == "isAdjacentTo") {
			int a, b;
			cin >> a >> b;
			cout << graph.isAdjacentTo(a, b) << endl;
		}
		else if (command == "MaxAdjacentNode") {
			int a;
			cin >> a;
			int max = graph.maxAdjacentNode(a);
			if (max == -1)
				cout << "None" << endl;
			else
				cout << max << endl;
		}
		else if (command == "SumAdjacentNode") {
			int a;
			cin >> a;
			int sum = graph.sumAdjacentNode(a);
			if (sum == 0)
				cout << "None" << endl;
			else
				cout << sum << endl;
		}
	}
}