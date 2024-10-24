#include <stdio.h>
#include <stdlib.h>

#define MAX 100001

typedef struct STATE {
	int position, time;
}State;

typedef struct QUEUE {
	State* data;
	int front, rear, capacity;
}Queue;

Queue* createQueue(int capacity) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->data = (State*)malloc(sizeof(State) * capacity);
	queue->front = 0;
	queue->rear = 0;
	queue->capacity = capacity;
	return queue;
}

void enqueue(Queue* queue, State state) {
	queue->data[queue->rear] = state;
	queue->rear = (queue->rear + 1) % queue->capacity;
}

State dequeue(Queue* queue) {
	State state = queue->data[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	
	return state;
}

int isEmpty(Queue* queue) {
	return queue->front == queue->rear;
}

int findMinTime(int N, int K) {
	if (N >= K)
		return N - K;

	int* visited = (int*)calloc(MAX, sizeof(int));
	Queue* queue = createQueue(MAX * 2);

	State initial = { N, 0 };
	enqueue(queue, initial);
	visited[N] = 1;

	while (!isEmpty(queue)) {
		State current = dequeue(queue);
		int pos = current.position;
		int time = current.time;

		if (pos == K) {
			free(visited);
			free(queue->data);
			free(queue);
			return time;
		}

		if (pos * 2 < MAX && !visited[pos * 2]) {
			State next = { pos * 2, time };
			enqueue(queue, next);
			visited[pos * 2] = 1;
		}

		if (pos > 0 && !visited[pos - 1]) {
			State next = { pos - 1, time + 1 };
			enqueue(queue, next);
			visited[pos - 1] = 1;
		}

		if (pos < MAX - 1 && !visited[pos + 1]) {
			State next = { pos + 1, time + 1 };
			enqueue(queue, next);
			visited[pos + 1] = 1;
		}
	}
	free(visited);
	free(queue->data);
	free(queue);
	return -1;
}

int main() {

	int N, K;
	scanf("%d %d", &N, &K);

	printf("%d\n", findMinTime(N, K));

	return 0;
}