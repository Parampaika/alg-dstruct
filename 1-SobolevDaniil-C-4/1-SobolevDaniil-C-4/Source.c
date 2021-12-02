#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#pragma warning(disable:4996)

#define LAST_VERT -1
#define MEM_ERROR -2
#define MEM_CONST 10
typedef enum {
	VISITED,
	NOT_VISITED
} state_t;


typedef struct vertex {
	int numConn;
	int* connVert;
	state_t visited;
}vertex;


typedef struct {
	int coun;
	int numElem;
	int* elements;
	int head;
	int rear;
}queue;



void startQueue(queue* queue, int number) {
	queue->elements = (int*)malloc((number + 1) * sizeof(int));
	queue->numElem = number;
	queue->head = 1;
	queue->rear = 1;
	queue->coun = 0;
}


void Push(queue* q, int x) {
	q->coun++;
	q->elements[q->rear] = x;
	if (q->rear == q->numElem) { q->rear = 1; }
	else {
		q->rear = q->rear + 1;
	}

}

int Pop(queue* q) {
	q->coun--;
	int x = q->elements[q->head];
	if (q->head == q->numElem) { 
		q->head = 1; 
	}
	else { 
		q->head = q->head + 1; 
	}
	return x;
}

int isempty(queue* q) {
	if (q->rear < q->head)    return 1;
	else  return 0;
}


void AddNewConnection(vertex* vertexes, int changVert, int addVert) {
	int placeForVert = LAST_VERT;
	int i = 0;
	int temp = -1;

	vertexes[changVert].connVert = realloc(vertexes[changVert].connVert, (vertexes[changVert].numConn + 1) * sizeof(int));
	if (!vertexes[changVert].connVert) {
		return;
	}

	for (i = 0; i < vertexes[changVert].numConn; i++) {
		if (vertexes[changVert].connVert[i] > addVert) {
			placeForVert = i;
			break;
		}
	}
	if (placeForVert == LAST_VERT) {
		vertexes[changVert].connVert[vertexes[changVert].numConn] = addVert;
	}
	if (placeForVert != LAST_VERT) {
		temp = vertexes[changVert].connVert[placeForVert];
		vertexes[changVert].connVert[placeForVert] = addVert;
		vertexes[changVert].connVert[vertexes[changVert].numConn] = temp;
	}
	vertexes[changVert].numConn++;
}


void FindConnections(vertex* vertexes, int knotsC) {
	int vert1 = -1, vert2 = -1;
	char* fNum;
	char* sNum;

	fNum = (char*)malloc(MEM_CONST * sizeof(char));
	if (!fNum) {
		return;
	}
	sNum = (char*)malloc(MEM_CONST * sizeof(char));
	if (!sNum) {
		return;
	}
	/*FILE* fp;
	char name[] = "Текст.txt";
	if ((fp = fopen(name, "r")) == NULL)
	{
		printf("Не удалось открыть файл");
	}*/
	while ((scanf( "%s %s", fNum, sNum) != EOF)) {
		vert1 = atoi(fNum);
		vert2 = atoi(sNum);
		AddNewConnection(vertexes, vert1, vert2);
		AddNewConnection(vertexes, vert2, vert1);
	}

	free(fNum);
	free(sNum);
}

void BFS(vertex* vertexes, queue* queue) {
	int cVert = -1;
	Push(queue, 0);
	vertexes[0].visited = VISITED;
	while (queue->coun > 0) {
		cVert = Pop(queue);
		printf("%d ", cVert);
		for (int i = 0; i < vertexes[cVert].numConn; i++) {
			if (vertexes[vertexes[cVert].connVert[i]].visited == NOT_VISITED) {
				Push(queue, vertexes[cVert].connVert[i]);
				vertexes[vertexes[cVert].connVert[i]].visited = VISITED;
			}
		}
	}
}

int main(void) {
	int number = 0;
	vertex* vertexes = NULL;
	queue queue;
	setlocale(LC_ALL, "Rus");
	scanf("%d", &number);

	vertexes = (vertex*) malloc(sizeof(vertex) * number);
	for (int i = 0; i < number; i++) {
		vertexes[i].numConn = 0;
		vertexes[i].connVert = NULL;
		vertexes[i].visited = NOT_VISITED;
	}

	FindConnections(vertexes, number);
	startQueue(&queue, number);
	BFS(vertexes, &queue);

	for (int i = 0; i < number; i++) {
		free(vertexes[i].connVert);
	}
	free(vertexes);

	return 0;
}