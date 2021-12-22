#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct pair
{
	int first;
	int second;

} pair_t;

typedef struct List
{
	int field;
	struct List* next;
} list_t;

typedef struct Queue
{
	struct List* head, * tail;
} queue_t;

queue_t* QueueCreate(int value)
{
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	if (!queue)
		return NULL;
	queue->head = (list_t*)malloc(sizeof(list_t));
	if (!queue->head)
		return NULL;
	queue->head->field = value;
	queue->head->next = NULL;
	queue->tail = queue->head;
	return queue;
}

pair_t* readPair(int T, FILE* file, int* numpair)
{
	int MaxNumpair = T * (T + 1) * 0.5;
	pair_t* pair = (pair_t*)malloc(sizeof(pair_t) * MaxNumpair);
	if (!pair)
		return NULL;
	int i = 0;
	while ((fscanf(file, "%i", &pair[i].first) != EOF) && (fscanf(file, "%i", &pair[i].second) != EOF))
	{
		if (pair[i].first == 0)
			break;
		i++;
	}
	*numpair = MaxNumpair;
	pair[i].first = 0;
	pair[i].second = 0;
	fclose(file);
	return pair;
}

void AddInQueue(queue_t* queue, int field)
{
	if (!queue->tail)
	{
		QueueCreate(field);
		return;
	}
	queue->tail->next = (list_t*)malloc(sizeof(list_t));
	if (!queue->tail->next)
	{
		perror("Memory error");
		return;
	}
	queue->tail = queue->tail->next;
	queue->tail->field = field;
	queue->tail->next = NULL;
}

void DeleteOutQueue(queue_t* queue)
{
	if (queue)
	{
		list_t* temp;
		temp = queue->head;
		queue->head = queue->head->next;
		free(temp);
	}
}

void ShirtArray(pair_t* pair, int number)
{
	int i = number;
	while ((pair[i].first != 0) || (pair[i].second != 0))
	{
		pair[i] = pair[i + 1];
		i++;
	}
	pair[i].first = 0;
	pair[i].second = 0;
}



int IsInQueue(queue_t* queue, int value)
{
	list_t* tmp = queue->head;
	while (tmp != NULL)
	{
		if (tmp->field == value)
		{
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

int FoundNextTask(pair_t* pair, int T, int top)
{
	int i = 0;
	int nextTask = T + 1, count;
	while ((pair[i].first != 0) || (pair[i].second != 0))
	{
		if (pair[i].first == top)
		{
			nextTask = pair[i].second;
			count = i;
			ShirtArray(pair, count);
			return nextTask;
		}
		i++;
	}
	return 0;
}



int IsInArr(int* arr, int size, int value)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] == value) {
			return 1;
		}
	}
	return 0;
}

void QueueDestroy(queue_t* queue)
{
	list_t* delete = NULL;
	while (queue->head != NULL) {
		delete = queue->head;
		queue->head = queue->head->next;
		free(delete);
	}
}

int* BuildSequence(int T, pair_t* pair, int numberPair)
{
	queue_t* queue = QueueCreate(1);
	int* sequence = (int*)malloc(sizeof(int) * T);
	if (!sequence)
		return NULL;
	int count = 0;
	while (count < T)
	{
		if (queue->head == NULL)
			break;
		int tmp = queue->head->field;
		int task = FoundNextTask(pair, T, tmp);
		while (task != 0)
		{
			if ((IsInQueue(queue, task) == 0) && (IsInArr(sequence, count + 1, task) == 0))
			{
				AddInQueue(queue, task);
			}
			task = FoundNextTask(pair, T, tmp);
		}
		DeleteOutQueue(queue);
		sequence[count] = tmp;
		count++;
	}
	if (count < T)
		return NULL;
	QueueDestroy(queue);
	free(pair);
	return sequence;
}

void Print(int* arr, int size, FILE* file)
{
	for (int i = 0; i < size; i++)
	{
		fprintf(file, "%i ", arr[i]);
	}
}

int main() {
	int T;
	int K;
	int numberPair = 0;
	int sum = 0, expen;

	FILE* F = fopen("input.txt", "r");
	FILE* f = fopen("output.txt", "w");
	if (!F) {
		return;
	}
		
	fscanf(F, "%i", &T);
	fscanf(F, "%i", &K);

	for (int i = 0; i < T; i++)
	{
		fscanf(F, "%i", &expen);
		sum = sum + expen;
	}

	if (sum > K)
	{
		fprintf(f, "0");
		fclose(F);
		fclose(f);
		return;
	}


	pair_t* pair = readPair(T, F, &numberPair);
	if (!pair)
	{
		fprintf(f, "0");
		fclose(f);
		return;
	}
	int* sequence = BuildSequence(T, pair, numberPair);
	if (!sequence)
	{
		fprintf(f, "0");
		fclose(f);
		return;
	}
	Print(sequence, T, f);
	free(sequence);
	fclose(f);


	return 0;
}