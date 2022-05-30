#include <iostream>
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
	int w;

	edge() {
		source = destination = NULL;
		prev = next = NULL;
		w = 0;
	}
	edge(vertex* source, vertex* destination, int w) {
		this->source = source;
		this->destination = destination;
		prev = next = NULL;
		this->w = w;
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
	void insertEdge(int sId, int dId, int w) {
		vertex* source = vList.find(sId);
		vertex* destination = vList.find(dId);
		int sMatrixId = source->matrixId;
		int dMatrixId = destination->matrixId;
		edge* e = new edge(source, destination, w);
		eList.insert(e);
		matrix[sMatrixId][dMatrixId] = matrix[dMatrixId][sMatrixId] = e;
	}
	void push(vector<int>& vec, int item) {
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i] == item)
				return;
			if (vec[i] > item) {
				vec.insert(vec.begin() + i, item);
				return;
			}
		}
		vec.push_back(item);
	}
	void recommend(int id, int defaultRelation, int findRelation) {
		vertex* v = vList.find(id);
		int MID = v->matrixId;

		vector<int> noRelations;
		vector<int> defaultRelations;
		for (int i = 0; i < matrix[MID].size(); i++) {
			if (matrix[MID][i]->w == 0 && i != MID)
				noRelations.push_back(i);
			if (matrix[MID][i]->w == defaultRelation)
				defaultRelations.push_back(i);
		}

		vector<int> result;
		for (int i = 0; i < defaultRelations.size(); i++) {
			for (int j = 0; j < noRelations.size(); j++) {
				int row = defaultRelations[i];
				int col = noRelations[j];
				if (matrix[row][col]->w == findRelation) {
					int resultId;
					if (matrix[row][col]->source->matrixId == row)
						resultId = matrix[row][col]->destination->id;
					else
						resultId = matrix[row][col]->source->id;
					push(result, resultId);
				}					
			}
		}

		if (result.size() == 0) {
			cout << 0 << endl;
			return;
		}
		for (int i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << endl;
	}
private:
	vector<vector<edge*>> matrix;
	VertexList vList;
	EdgeList eList;
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
		int id, w;
		cin >> id >> w;
		if (w == 0)
			graph.recommend(id, 1, 1);
		if (w == 1)
			graph.recommend(id, 1, 2);
	}
}