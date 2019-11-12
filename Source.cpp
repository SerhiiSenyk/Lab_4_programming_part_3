#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Graph;
void display(int **graph, const int countEdges);
void DFS(vector<vector<bool>> &matrix, vector<vector<int>> &component,
	vector<bool> &visited, int countVertex, int start, int k);
int convert(Graph **graph, int **gr, int countEdges, vector<int> &vertexArray);
void convertToMatrix(Graph **graph, vector<vector<bool>> &matrix, int countEdges, int countVertex);
//Depth - first search
vector<vector<int>> searchComponents(vector<vector<bool>> &matrix, int countVertex);
void searhPair(vector<vector<int>> &comp, vector<int> &vertexArray);
int** readWithFile(int &countEdges);
struct Graph {
	unsigned short int vertex;
	unsigned short int value;
};

int main()
{
	const int N = 2;
	int countEdges = 0;
	int **graph = readWithFile(countEdges);
	display(graph, countEdges);
	Graph **graph1 = new Graph*[countEdges];
	for (int i = 0; i < countEdges; ++i)
		graph1[i] = new Graph[N];
	vector<int> vertexArray;
	int countVertex = convert(graph1, graph, countEdges, vertexArray);
	vector<vector<bool>> matrix(countVertex);
	for (int i = 0; i < countVertex; ++i)
		matrix[i].resize(countVertex);
	convertToMatrix(graph1, matrix, countEdges, countVertex);
	vector<vector<int>> comp = searchComponents(matrix, countVertex);
	matrix.~vector();
	searhPair(comp, vertexArray);

	for (int i = 0; i < countEdges; ++i) {
		free(graph[i]);
		delete[] graph1[i];
	}
	free(graph);
	delete[] graph1;

	comp.~vector();
	vertexArray.~vector();
	system("pause");
	return 0;
}

void searhPair(vector<vector<int>> &comp, vector<int> &vertexArray)
{
	int countPair = 0;
	printf("Out :\n");
	for (int i = 0; i < comp.size() - 1; ++i) {
		for (int j = 0; j < comp[i].size(); ++j) {
			for (int k = i + 1; k < comp.size(); ++k) {
				for (int z = 0; z < comp[k].size(); ++z) {
					if ((vertexArray[comp[i][j]] % 2 && !(vertexArray[comp[k][z]] % 2)) ||
						(!(vertexArray[comp[i][j]] % 2) && vertexArray[comp[k][z]] % 2)) {
						printf("%d/%d  ", vertexArray[comp[i][j]], vertexArray[comp[k][z]]);
						++countPair;
					}
				}
			}
		
		}
	}
	printf("\nPair : %d\n", countPair);
}

void convertToMatrix(Graph **graph, vector<vector<bool>> &matrix,int countEdges,int countVertex)
{
	for (size_t i = 0; i < countEdges; ++i) {
		matrix[graph[i][1].vertex][graph[i][0].vertex] = true;
		matrix[graph[i][0].vertex][graph[i][1].vertex] = true;
	}
	return;
}

int convert(Graph **graph, int **gr, int countEdges, vector<int> &vertexArray)
{
	int currentVertex = 0;
	vertexArray.push_back(**gr);
	int countVertex = 1;
	for (size_t i = 0; i < countEdges; ++i) {
		for (size_t j = 0; j < 2; ++j) {
			int key = graph[i][j].value = gr[i][j];
			for (int k = 0; k < countVertex; ++k) {
				if (key == vertexArray[k]) {
					currentVertex = k;
					break;
				}
				if (k == countVertex - 1) {
					currentVertex = ++countVertex;
					vertexArray.push_back(key);
				}
			}
			graph[i][j].vertex = currentVertex;
		}
	}
	for (int i = 0; i < countEdges; ++i){
		for (int j = 0; j < 2; ++j) {
			gr[i][j] = graph[i][j].vertex;
		}
	}
	return countVertex;
}

vector<vector<int>> searchComponents(vector<vector<bool>> &matrix, int countVertex)
{
	vector<bool> visited(countVertex);
	vector<vector<int>> components;
	int countComponents = 0;
	for (size_t i = 0; i < countVertex; ++i) {
		if (!visited[i]) {
			++countComponents;
			components.resize(countComponents);
			DFS(matrix, components, visited, countVertex, i, countComponents - 1);
		}
	}
	return components;
}

void DFS(vector<vector<bool>> &matrix, vector<vector<int>> &component,
	vector<bool> &visited, int countVertex,int start, int k)
{
	vector<int> stack(countVertex);
	int top, v, i;
	top = i = v = 0;
	stack[0] = start;
	visited[start] = true;
	component[k].push_back(start);
	while (top >= 0) {
		v = stack[top];
		i = 0;
		while (i < countVertex && (!matrix[v][i] || visited[i]))
			++i;
		if (i < countVertex) {
			++top;
			stack[top] = i;
			visited[i] = true;
			component[k].push_back(i);
		}
		else
			--top;
	}
	stack.~vector();
}

int** readWithFile(int &countEdges)
{
	FILE *ptrFile = NULL;
	fopen_s(&ptrFile, "graph.txt", "r");
	if (ptrFile == NULL) {
		perror("Error open file <graph.txt> ");
		cout << "Press any key to continue program\n";
		exit(0);
	}
	fscanf_s(ptrFile, "%d", &countEdges);
	if (countEdges < 0 || countEdges > 10000)
		exit(0);
	int **graph = (int**)calloc(countEdges, sizeof(int*));
	for (int i = 0; i < countEdges; ++i)
		graph[i] = (int*)calloc(2, sizeof(int));
	int i = 0;
	while (!feof(ptrFile)) {
		fscanf_s(ptrFile, "%d %d", &graph[i][0], &graph[i][1]);
		++i;
	}
	fclose(ptrFile);
	return graph;
}

void display(int **graph, const int countEdges)
{
	printf("In :\n");
	cout << countEdges << endl;
	for (int i = 0; i < countEdges; ++i) {
		for (int j = 0; j < 2; ++j)
			cout << graph[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}
