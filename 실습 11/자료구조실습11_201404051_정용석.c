#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VERTICES 26 //정점의 최대 갯수

//탐색을 위한 큐 자료구조

int visited[MAX_VERTICES];

#define INIT_QUEUE() { front = rear = 1;}
#define ENQUEUE(v) {queue[++front] = v;}
#define DEQUEUE() ((front >= rear) ? queue[++rear] : -1)
#define ISEMPTY() (front < rear)

int queue[MAX_VERTICES];
int front, rear;

typedef struct _Graph {
	int nVertices;		//정점의 개수	
	int nEdges;			//간선의 개수
	int vertex[MAX_VERTICES];
	//그래프에 존재하는 vertex를 구분
	int edge[MAX_VERTICES][MAX_VERTICES];
	//그래프에 존재하는 edge를 구분
} Graph;

// Graph g를 초기화한다.
void initGraph(Graph *g)
{
	int i, j;
	g->nVertices = 0;
	g->nEdges = 0;

	for (i = 0; i < MAX_VERTICES; i++) {
		g->vertex[i] = 0;
		for (j = 0; j < MAX_VERTICES; j++)
			g->edge[i][j] = 0;
	}
}

// Graph g의 vertex 리스트와 edge 리스트를 출력한다.
void printGraph(Graph *g)
{
	int i, j, ne = 0;

	//정점 집합 출력
	printf("V(G) = { ");
	for (i = 0; i < g->nVertices; i++) {
		printf("%c", 'A' + i);
		if (i < g->nVertices - 1)
			printf(", ");
	}
	printf(" }\n");

	// 간선 집합 출력
	printf("E(G) = { ");
	for (i = 0; i < MAX_VERTICES; i++)
		for (j = i + 1; j < MAX_VERTICES; j++) {
			if (g->edge[i][j] > 0) {
				printf("(%c, %c)", 'A' + i, 'A' + j);
				if (++ne < g->nEdges)
					printf(", ");
			}
		}
	printf(" }\n");
}

// Graph g에 vertex v를 추가한다.
int insertVertex(Graph *g, int v)
{
	if (!(0 <= v && v < MAX_VERTICES))
		return 0; // 정점 범위 오류
	if (g->vertex[v] == 1)
		return 0; // 이미 존재하는 정점 오류
	
	// 정점 v의 존재 입력 및 정점 갯수 증가
	g->vertex[v] = 1; 
	g->nVertices++;

	return -1;
}

// Graph g에 v1-v2를 연결하는 edge를 추가한다. 
int insertEdge(Graph *g, int v1, int v2)
{
	if (!(0 <= v1 && v1 < MAX_VERTICES))
		return 0; // 정점 범위 오류
	if (g->vertex[v1] == 0)
		return 0; // 없는 정점 오류
	if (!(0 <= v2 && v2 < MAX_VERTICES))
		return 0; // 정점 범위 오류
	if (g->vertex[v2] == 0)
		return 0; // 없는 정점 오류

	//간선 존재 유무 추가 및 간선의 갯수 증가
	g->edge[v1][v2] = 1;
	g->edge[v2][v1] = 1;
	g->nEdges++;

	return -1; // 성공
}

// 그래프 파일을 읽어 Graph g에 저장한다.
int readGraphFile(Graph *g, char* fname) {
	FILE *fp = fopen(fname, "r");
	int nv, ne, i;
	int v1, v2;
	char ch1, ch2;

	if (fp == NULL) return 0; // 파일 오류

	initGraph(g);

	// 정점 갯수를 읽어 정점 추가
	fscanf(fp, "%d", &nv);
	for (i = 0; i < nv; i++)
		insertVertex(g, i);

	// 간선 갯수와 간선 정보를 읽어 간선 추가
	fscanf(fp, "%d", &ne);
	for (i = 0; i < ne; i++) {
		// 첫번째 정점 읽기
		do {
			fscanf(fp, "%c", &ch1);
		} while (ch1 < 'A' || 'Z' < ch1);
		v1 = ch1 - 'A';
		// 두번째 정점 읽기
		do {
			fscanf(fp, "%c", &ch2);
		} while (ch2 < 'A' || 'Z' < ch2);
		v2 = ch2 - 'A';
		// 간선 (v1, v2) 추가
		insertEdge(g, v1, v2);
	}
	fclose(fp);

	return -1;
}

void dfsCore(Graph *g, int v) {
	int i;
	visited[v] = 1;
	printf("%c ", 'A' + v); // printf v 값
	//모든 정점 i에서 v와 인접한 정점들 중 방문하지 않은 정점에 관해서 재귀
	for (i = 0; i < MAX_VERTICES; i++) {
		if (g->edge[v][i] == 1)
			if(visited[i] == 0)
				dfsCore(g, i);
	}
}

void depthFirstSearch(Graph *g, int v) {
	int i;

	//visited 플래그 초기화
	for (i = 0; i < MAX_VERTICES; i++)
		visited[i] = 0;

	//정점 v부터 그래프 g의 깊이 우선 탐색 시작
	printf("Depth First Search :");
	dfsCore(g, v);
	printf("\n");
}

void breathFirstSearch(Graph *g, int v) {
	int w, i;

	//큐 초기화
	INIT_QUEUE();

	//visited 플래그 초기화
	for (i = 0; i < MAX_VERTICES; i++)
		visited[i] = 0;

	printf("Breath First Search :");

	visited[v] = 1;
	printf("%c ", 'A' + v); // print v값
	ENQUEUE(v);
	while (!ISEMPTY()) {
		v = DEQUEUE();
		for (i = 0; i < MAX_VERTICES; i++) {
			//v의 인접한 정점 i에 관해서 방문하지 않았을 때
			if (g->edge[i][v] == 1)
				if (visited[i] == 0) {
					visited[i] = 1;
					printf("%c ", 'A' + i); //print i값
					ENQUEUE(i);
				}
		}
	}
	printf("\n");
}

void main()
{
	Graph G;

	readGraphFile(&G, "graph.txt");
	printGraph(&G);

	depthFirstSearch(&G, 0);
	breathFirstSearch(&G, 0);

	system("pause");
}