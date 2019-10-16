//09.10.2019
/*Весілля та племена
Вождь Ваі - Ву з острова Пасхи вирішив поміняти традиції одруження на острові.
Раніше усі одружувались всередині свого племені.Але після курсу біології на Coursera
Ваі - Ву дізнався, що змішування генів - це корисна штука.Тому він попросив усіх голів
племен підготувати списки молодих хлопців / дівчат, і спробує організувати шлюби між
племенами.
Вашим завдання буде проаналізувати списки, та сказати Ваі - Ву скільки можливих пар з
різних племен він може скласти.
Формат списків племен :
● Кожен юнак / дівчина - це ціле число
● Юнаки - непарні числа, дівчата - парні
● У кожному рядку - два числа, які означають що юнак чи дівчина належать до
одного племені.Наприклад :
	1 2
	2 4
	3 5
	Описує два племені - в одному є хлопець 1 та двоє дівчат 2 та 4, а в іншому
	племені - двоє хлопців 3 та 5.
	Вхідні дані :
Перший рядок містить кількість пар N
Наступні N рядків містять пари людей з різних племен
Вихідні дані :
Кількість можливих комбінацій пар таких, що хлопець і дівчина походять з різних
племен.
Обмеження :
	0 < N < 10000
	Приклади:
In:
3
1 2
2 4
3 5
Out :
   4 (Можливі пари - 2 / 3, 2 / 5, 4 / 3, 4 / 5)

	In :
	5
	1 2
	2 4
	1 3
	3 5
	8 10
	Out:
6 (Можливі пари - 1 / 8, 1 / 10, 3 / 8, 3 / 10, 5 / 8, 5 / 10)*/
/*1 2
  1 3
  2 4
  3 5
  8 10*/




  //виділити компоненти звязності в графі 
  //алгоритм DFS
  //звичаним перебором пройтися по всіх елементах
  //з різних компонент звязності 
  //пошук в глибину або в ширину
  //список ребер посортованих по першій вершині
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
struct Graph;

void enter(int **graph);
void display(int **graph, const int countEdges);
void DFS(vector<vector<bool>> &matrix, vector<vector<int>> &component,
	vector<bool> &visited, int countVertex, int start, int k);
int convert(Graph **graph, int **gr, int countEdges, vector<int> &vertexArray);
void convertToMatrix(Graph **graph, vector<vector<bool>> &matrix, int countEdges, int countVertex);
//Depth - first search
vector<vector<int>> searchComponents(vector<vector<bool>> &matrix, int countVertex);
void searhPair(vector<vector<int>> &comp, vector<int> &vertexArray);
struct Graph {
	unsigned short int vertex;
	unsigned short int value;
};

int main()
{
	const int countEdges = 5;
	const int N = 2;
	int **graph = (int**)calloc(countEdges, sizeof(int*));
	for (int i = 0; i < countEdges; ++i)
		graph[i] = (int*)calloc(N, sizeof(int));
	enter(graph);
	display(graph, countEdges);

	cout << sizeof(vector<bool>) << endl;
	display(graph, countEdges);




	//convertToMatrix(graph, countEdges);
	Graph **graph1 = new Graph*[countEdges];
	for (int i = 0; i < countEdges; ++i)
		graph1[i] = new Graph[2];
	vector<int> vertexArray;
	int countVertex = convert(graph1, graph, countEdges, vertexArray);
	vector<vector<bool>> matrix(countVertex);
	for (int i = 0; i < countVertex; ++i)
		matrix[i].resize(countVertex);
	convertToMatrix(graph1, matrix, countEdges, countVertex);
	//DFS(matrix, countVertex);
	vector<vector<int>> comp = searchComponents(matrix, countVertex);


	searhPair(comp, vertexArray);
	system("pause");
	return 0;
}

void searhPair(vector<vector<int>> &comp, vector<int> &vertexArray)
{
	int countPair = 0;
	for (int i = 0; i < comp.size() - 1; ++i) {
		for (int j = 0; j < comp[i].size(); ++j) {
			//cout << vertexArray[comp[i][j]] << "   ";
			for (int k = i + 1; k < comp.size(); ++k) {
				for (int z = 0; z < comp[k].size(); ++z) {
					//printf("%d/%d  ", vertexArray[comp[i][j]], vertexArray[comp[k][z]]);
					if ((vertexArray[comp[i][j]] % 2 && !(vertexArray[comp[k][z]] % 2)) ||
						(!(vertexArray[comp[i][j]] % 2) && vertexArray[comp[k][z]] % 2)) {
						printf("%d/%d  ", vertexArray[comp[i][j]], vertexArray[comp[k][z]]);
						++countPair;
					}
				}
			}
		
		}
		cout << endl;
	}
	cout << countPair << endl;
	//cout << vertexArray[comp[i][j]] << "   ";
}



void convertToMatrix(Graph **graph, vector<vector<bool>> &matrix,int countEdges,int countVertex)
{
	for (size_t i = 0; i < countEdges; ++i) {
		matrix[graph[i][1].vertex][graph[i][0].vertex] = true;
		matrix[graph[i][0].vertex][graph[i][1].vertex] = true;
	}
	for (int i = 0; i < countVertex; ++i) {
		for (int j = 0; j < countVertex; ++j) {
			cout << matrix[i][j] << "  ";
			
		}
		cout << endl;
	}
	//vector<int> list[10];
	////for (int i = 0; i < countVertex; ++i)
	//	//list.resize(countVertex);
	//for (size_t i = 0; i < countEdges; ++i) {
	//	list[graph[i][0].vertex].push_back(graph[i][1].vertex);
	//	//list[graph[i][1].vertex].push_back(graph[i][0].vertex);
	//}
	//cout << endl;
	//for (int i = 0; i < countVertex; ++i) {
	//	for (int j = 0; j < list[i].size(); ++j) {
	//		cout << list[i][j] << "  ";
	//	}
	//	cout << endl;
	//}
	return;
}

int convert(Graph **graph, int **gr, int countEdges, vector<int> &vertexArray)
{
	//int *vertexArray = (int*)calloc(countEdges*2, sizeof(int));

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

	//free(vertexArray);
	cout << countVertex << endl;
	for (int i = 0; i < countEdges; ++i) {
		for (int j = 0; j < 2; ++j)
			cout << graph[i][j].value << "  " << graph[i][j].vertex << "  ";
		cout << endl;
	}
	cout << endl;
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
	cout << endl << countComponents;
	cout << "Comp:";
	cout << endl;
	for (int i = 0; i < components.size(); ++i) {
		for (int j = 0; j < components[i].size(); ++j) {
			cout << ' ' << components[i][j];
		}
		cout << endl;
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
	cout << endl;
	for (int i = 0; i < countVertex; ++i) {
		cout << visited[i] << "  ";
	}
	cout << endl;
	stack.~vector();
}

void enter(int **graph) 
{
	graph[0][0] = 1;
	graph[0][1] = 2;
	graph[1][0] = 2;
	graph[1][1] = 4;
	graph[2][0] = 1;
	graph[2][1] = 3;
	graph[3][0] = 3;
	graph[3][1] = 5;
	graph[4][0] = 8;
	graph[4][1] = 10;	
}

//
//1 2
//2 4
//1 3
//3 5
//8 10
void display(int **graph, const int countEdges)
{
	for (int i = 0; i < countEdges; ++i) {
		for (int j = 0; j < 2; ++j)
			cout << graph[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}
