#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>>convertMatrixToList(const string& filename) {
	ifstream file(filename);
	vector <vector<int>>matrix;
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		int num;
		vector<int>row;

		while (ss >> num) {
			row.push_back(num);
		}

		if (!row.empty()) {
			matrix.push_back(row);
		}

	}
	int n = matrix.size();
	vector<vector<int>>adjList(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] != 0) {
				adjList[i].push_back(j);
			}
		}
	}
	return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Cannot open file.\n";
		return {};
	}

	int n;
	file >> n;
	file.ignore();

	vector<vector<int>>matrix(n, vector<int>(n, 0));
	string line;

	for (int i = 0; i < n && getline(file, line); ++i) {
		stringstream ss(line);
		int neighbor;
		while (ss >> neighbor) {
			matrix[i][neighbor] = 1;
		}
	}
	return matrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i])
				return true;
		}
	}
	return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) {
	int cnt = 0;
	int n = adjMatrix.size();
	bool directed = isDirected(adjMatrix);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cnt += adjMatrix[i][j];
		}
	}
	return directed ? cnt : cnt / 2;
	
}

//danh sach cac dinh co lap(khong co canh noi)
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int>isolated;

	for (int i = 0; i < n; i++) {
		bool hasEdge = false;
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] || adjMatrix[j][i]) {
				hasEdge = true;
				break;
			}
		}
		if (!hasEdge)isolated.push_back(i);
	}
	return isolated;
}

//do thi day du undirected graph
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && adjMatrix[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

//kiem tra do thi hai phia (bipartite)
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix) {
	int n = adjMatrix.size();

	vector<int> color(n, -1);

	for (int i = 0; i < n; i++) {
		if (color[i] == -1) {
			queue <int>q;
			q.push(i);
			color[i] = 0;
			while (!q.empty()) {
				int j = q.front();
				q.pop();
				for (int k = 0; k < n; k++) {
					if (adjMatrix[j][k]) {
						if (color[k] == -1) {
							color[k] = 1 - color[j];
							q.push(k);
						}
						else if (color[k] == color[j]) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	if (!isBipartite(adjMatrix))return false;

	int n = adjMatrix.size();
	vector<int>color(n, -1);
	vector<int>part[2];

	for (int i = 0; i < n; i++) {
		if (color[i] == -1) {
			queue <int>q;
			q.push(i);
			color[i] = 0;
			part[0].push_back(i);
			while (!q.empty()) {
				int j = q.front();
				q.pop();
				for (int k = 0; k < n; k++) {
					if (adjMatrix[j][k]) {
						if (color[k] == -1) {
							color[k] = 1 - color[j];
							q.push(k);
							part[color[k]].push_back(k);
						}
					}
				}
			}
		}
	}

	for (int u : part[0]) {
		for (int v : part[1]) {
			if (adjMatrix[u][v] == 0) {
				return false;
			}
		}
	}
	return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector <vector<int>>result(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] || adjMatrix[j][i]) {
				result[i][j] = result[j][i] = 1;
			}
		}
	}
	return result;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector <vector<int>>complement(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				complement[i][j] = adjMatrix[i][j] ? 0 : 1;
			}
		}
	}
	return complement;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> inDegree(n, 0), outDegree(n, 0);

	for (int u = 0; u < n; ++u) {
		for (int v = 0; v < n; ++v) {
			if (adjMatrix[u][v] > 0) {
				outDegree[u] += adjMatrix[u][v];
				inDegree[v] += adjMatrix[u][v];
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		if (inDegree[i] != outDegree[i]) return {};
	}

	int start = -1;
	for (int i = 0; i < n; ++i) {
		if (outDegree[i] > 0) {
			start = i;
			break;
		}
	}

	if (start == -1) return {};

	vector<vector<int>> graph = adjMatrix;
	stack<int> st;
	vector<int> cycle;
	st.push(start);

	while (!st.empty()) {
		int u = st.top();
		int v = -1;
		for (int i = 0; i < n; ++i) {
			if (graph[u][i] > 0) {
				v = i;
				break;
			}
		}
		if (v == -1) {
			cycle.push_back(u);
			st.pop();
		}
		else {
			graph[u][v]--;
			st.push(v);
		}
	}

	reverse(cycle.begin(), cycle.end());

	int edgeCount = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			edgeCount += adjMatrix[i][j];

	if ((int)cycle.size() == edgeCount + 1) return cycle;

	return {};
}

void dfsHelper(int u, const vector <vector<int>>& adjMatrix, vector<vector<int>>& tree, vector<bool>& visited) {
	visited[u] = true;
	int n = adjMatrix.size();
	for (int v = 0; v < n; v++) {
		if (adjMatrix[u][v] && !visited[v]) {
			tree[u][v] = tree[v][u] = 1;
			dfsHelper(v, adjMatrix, tree, visited);
		}
	}
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	dfsHelper(start, adjMatrix, tree, visited);
	return tree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<bool>visited(n, false);
	vector<vector<int>>tree(n, vector<int>(n, 0));
	queue <int>q;
	q.push(start);
	visited[start] = true;

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] && !visited[v]) {
				visited[v] = true;
				tree[u][v] = tree[v][u] = 1;
				q.push(v);
			}
		}
	}
	return tree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	queue<int> q;
	q.push(u);
	visited[u] = true;

	while (!q.empty()) {
		int curr = q.front();
		q.pop();

		if (curr == v)return true;

		for (int i = 0; i < n; i++) {
			if (adjMatrix[curr][i] && !visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}
	return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX);
	vector<int> prev(n, -1);
	vector<bool> visited(n, false);

	dist[start] = 0;

	for (int i = 0; i < n; ++i) {
		int u = -1;
		int minDist = INT_MAX;
		for (int j = 0; j < n; ++j) {
			if (!visited[j] && dist[j] < minDist) {
				minDist = dist[j];
				u = j;
			}
		}
		if (u == -1) break;
		visited[u] = true;

		for (int v = 0; v < n; v++) {
			if (adjMatrix[u][v] > 0 && dist[u] + adjMatrix[u][v] < dist[v]) {
				dist[v] = dist[u] + adjMatrix[u][v];
				prev[v] = u;
			}
		}
	}
	vector<int>path;
	if (dist[end] == INT_MAX) return path;
	for (int at = end; at != -1; at = prev[at])
		path.push_back(at);
	reverse(path.begin(), path.end());
	return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> dist(n, INT_MAX), prev(n, -1);
	dist[start] = 0;

	for (int k = 0; k < n - 1; k++) {
		for (int u = 0; u < n; u++) {
			for (int v = 0; v < n; v++) {
				if (adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
					dist[v] = dist[u] + adjMatrix[u][v];
					prev[v] = u;
				}
			}
		}
	}
	vector<int>path;
	if (dist[end] == INT_MAX)return path;
	for (int at = end; at != -1; at = prev[at])path.push_back(at);
	reverse(path.begin(), path.end());
	return path;
}