#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
}NODE;

typedef struct queue {
	NODE* head;
	NODE* tail;
	int count;
}QUEUE;

QUEUE* initQueue() {
	QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
	q->head = (NODE*)malloc(sizeof(NODE));
	q->head->next = 0;
	q->tail = q->head;
	q->count = 0;
	return q;
}

void qpush(QUEUE* q, int data) {
	q->tail->data = data;
	q->tail->next = (NODE*)malloc(sizeof(NODE));
	q->tail = q->tail->next;
	q->tail->next = 0;
	q->count++;
}

int qpop(QUEUE* q) {
	int data = q->head->data;
	NODE* p = q->head;
	q->head = q->head->next;
	q->count--;
	free(p);
	return data;
}

int isPrime(int n) {
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

int put(int n, int m, int p) {
	return n - (n / p % 10) * p + m * p;
}

int main() {
	char che[10001] = {};
	int i, j;
	for (i = 2; i < 10001; i++) {
		if (che[i] == 0)
			for (j = i * i; j < 10001; j++)
				che[j] = 1;
	}

	int t;
	scanf("%d", &t);
	
	while (t--) {
		char check[10001] = {};
		int p, q, s, count, k = 0;
		scanf("%d %d", &p, &q);
		QUEUE* que = initQueue();
		qpush(que, p);
		for (s = 0; que->count; s++) {
			count = que->count;
			int data, tmp;
			while (count--) {
				data = qpop(que);
				if (data == q) {
					break;
				}
				for (i = 1; i < 1001; i *= 10) {
					for (j = 0; j < 10; j++) {
						tmp = put(data, j, i);
						if (tmp > 1000 && che[tmp] == 0 && check[tmp] == 0) {
							qpush(que, tmp);
							check[tmp] = 1;
						}
					}
				}
			}
		}
		if (k == 0)
			printf("Impossible\n");
		else
			printf("%d\n", k);
	}
	return 0;
}


/*

3
1033 8179
1373 8017
1033 1033

*/