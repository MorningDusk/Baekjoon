#include <stdio.h>
#include <stdlib.h>

#define MAX 220

typedef struct QUEUE {
	int* data;
	int front, rear, size;
}Queue;

int N, K, Start, End, Cnt, Answer;
int Belt[MAX];
int Visit[MAX];
Queue* Robot;

Queue* createQueue(int capacity) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->data = (int*)malloc(capacity * sizeof(int));
	queue->front = 0;
	queue->rear = 0;
	queue->size = 0;
	return queue;
}

void push(Queue* queue, int value) {
	queue->data[queue->rear] = value;
	queue->rear = (queue->rear + 1) % MAX;
	queue->size++;
}

int pop(Queue* queue) {
	int value = queue->data[queue->front];
	queue->front = (queue->front + 1) % MAX;
	queue->size--;
	return value;
}

int queueSize(Queue* queue) {
	return queue->size;
}

void Input() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= 2 * N; i++)
		scanf("%d", &Belt[i]);
}

void moveBelt() {
	Start--;
	End--;
	if (Start < 1)
		Start = 2 * N;
	if (End < 1)
		End = 2 * N;
}

void moveRobot() {
	int Size = queueSize(Robot);
	for (int i = 0; i < Size; i++) {
		int Cur = pop(Robot);
		Visit[Cur] = 0;

		if (Cur == End)
			continue;
		int Next = Cur + 1;
		if (Next > 2 * N)
			Next = 1;
		if (Belt[Next] >= 1 && Visit[Next] == 0) {
			Belt[Next]--;
			if (Belt[Next] == 0)
				Cnt++;
			if (Next == End)
				continue;
			Visit[Next] = 1;
			push(Robot, Next);
		}
		else {
			Visit[Cur] = 1;
			push(Robot, Cur);
		}
	}
}

void makeRobot() {
	if (Visit[Start] == 0 && Belt[Start] >= 1) {
		Visit[Start] = 1;
		Belt[Start]--;
		push(Robot, Start);
		if (Belt[Start] == 0)
			Cnt++;
	}
}

void Solution() {
	Start = 1;
	End = N;
	while (Cnt < K) {
		Answer++;
		moveBelt();
		moveRobot();
		makeRobot();
	}
	printf("%d\n", Answer);
}

void Solve() {
	Input();
	Solution();
}

int main() {
	Robot = createQueue(MAX);
	Answer = 0;
	Cnt = 0;
	for (int i = 0; i < MAX; i++)
		Visit[i] = 0;
	Solve();
	free(Robot->data);
	free(Robot);
	return 0;
}