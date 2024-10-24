#include <stdio.h>
#include <stdlib.h>

#define MAX 101
#define INF 987654321

typedef struct QUEUE {
	int* data;
	int front, rear, size;
}Queue;

int board[MAX];
int visited[MAX];
int N, M;

Queue* createdQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = (int*)malloc(sizeof(int) * MAX);
	q->front = 0;
	q->rear = 0;
	q->size = 0;
	return q;
}

void enqueue(Queue* q, int value) {
	q->data[q->rear] = value;
	q->rear = (q->rear + 1) % MAX;
	q->size++;
}

int dequeue(Queue* q) {
	int value = q->data[q->front];
	q->front = (q->front + 1) % MAX;
	q->size--;
	return value;
}

int isEmpty(Queue* q) {
	return q->size == 0;
}

void freeQueue(Queue* q) {
	free(q->data);
	free(q);
}

int findMinDiceRolls() {
	Queue* q = createdQueue();
	for (int i = 0; i < MAX; i++)
		visited[i] = INF;
	visited[1] = 0;
	enqueue(q, 1);
	while (!isEmpty(q)) {
		int current = dequeue(q);
		for (int dice = 1; dice <= 6; dice++) {
			int next = current + dice;
			if (next > 100)
				continue;
			if (board[next] != 0)
				next = board[next];
			if (visited[next] > visited[current] + 1) {
				visited[next] = visited[current] + 1;
				enqueue(q, next);
			}
		}
	}
	int result = visited[100];
	freeQueue(q);
	return result;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < MAX; i++)
		board[i] = 0;
	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		board[x] = y;
	}
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		board[u] = v;
	}
	printf("%d\n", findMinDiceRolls());
	return 0;
}