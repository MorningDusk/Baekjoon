#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int front_radar;
    int corner_radar;
} State;

typedef struct Node {
    State state;
    int depth;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, State state, int depth) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->state = state;
    newNode->depth = depth;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

Node* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

int minTransfers(int n, int m, int k) {
    if (k == 0) return INT_MAX;
    Queue* q = createQueue();
    State initialState;
    initialState.front_radar = n;
    initialState.corner_radar = m;
    enqueue(q, initialState, 0);

    // 동적 메모리 할당
    int** visited = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; ++i) {
        visited[i] = (int*)malloc((m + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            visited[i][j] = 0;

    while (q->front != NULL) {
        Node* node = dequeue(q);
        State state = node->state;
        int depth = node->depth;
        free(node);

        if (state.front_radar == 0 && state.corner_radar == 0) {
            while (q->front != NULL) {
                Node* temp = dequeue(q);
                free(temp);
            }
            free(q);
            for (int i = 0; i <= n; ++i) {
                free(visited[i]);
            }
            free(visited);
            return depth;
        }

        if (visited[state.front_radar][state.corner_radar]) continue;
        visited[state.front_radar][state.corner_radar] = 1;

        for (int i = 0; i <= k; ++i) {
            for (int j = 0; j <= k - i; ++j) {
                if (i == 0 && j == 0) continue;
                if (state.front_radar >= i && state.corner_radar >= j) {
                    State newState;
                    newState.front_radar = state.front_radar - i;
                    newState.corner_radar = state.corner_radar - j;
                    enqueue(q, newState, depth + 1);
                }
                if (i > 0 && state.front_radar + i <= n) {
                    State newState;
                    newState.front_radar = state.front_radar + i;
                    newState.corner_radar = state.corner_radar + j;
                    enqueue(q, newState, depth + 1);
                }
            }
        }
    }

    free(q);
    for (int i = 0; i <= n; ++i) {
        free(visited[i]);
    }
    free(visited);
    return INT_MAX;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int k = 1;
        while (1) {
            int result = minTransfers(n, m, k);
            if (result != INT_MAX) {
                printf("%d %d\n", k, result);
                break;
            }
            k++;
        }
    }
    return 0;
}
