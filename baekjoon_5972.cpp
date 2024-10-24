#include <stdio.h>
#include <stdlib.h>

#define MAX 50001
#define INF 1000000000

// ���� ����Ʈ�� ��� ����ü
typedef struct Node {
    int vertex;
    int cost;
    struct Node* next;
} Node;

// �켱���� ť�� ��� ����ü
typedef struct {
    int vertex;
    int cost;
} PQNode;

// �켱���� ť ����ü
typedef struct {
    PQNode heap[MAX * 2];
    int size;
} PriorityQueue;

// �׷����� ���� ����Ʈ
Node* adj[MAX];
int dist[MAX];
int visited[MAX];

// �켱���� ť ����
void push(PriorityQueue* pq, int vertex, int cost) {
    int idx = ++pq->size;
    while (idx != 1 && cost < pq->heap[idx / 2].cost) {
        pq->heap[idx] = pq->heap[idx / 2];
        idx /= 2;
    }
    pq->heap[idx].vertex = vertex;
    pq->heap[idx].cost = cost;
}

PQNode pop(PriorityQueue* pq) {
    PQNode ret = pq->heap[1];
    PQNode temp = pq->heap[pq->size--];
    int parent = 1, child = 2;

    while (child <= pq->size) {
        if (child < pq->size && pq->heap[child].cost > pq->heap[child + 1].cost) {
            child++;
        }
        if (temp.cost <= pq->heap[child].cost) break;
        pq->heap[parent] = pq->heap[child];
        parent = child;
        child *= 2;
    }
    pq->heap[parent] = temp;
    return ret;
}

// �׷����� ���� �߰�
void addEdge(int u, int v, int cost) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->cost = cost;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// ���ͽ�Ʈ�� �˰���
int dijkstra(int start, int end, int n) {
    PriorityQueue pq;
    pq.size = 0;

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[start] = 0;
    push(&pq, start, 0);

    while (pq.size > 0) {
        PQNode current = pop(&pq);
        int u = current.vertex;

        if (visited[u]) continue;
        visited[u] = 1;

        for (Node* temp = adj[u]; temp != NULL; temp = temp->next) {
            int v = temp->vertex;
            int cost = temp->cost;

            if (!visited[v] && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                push(&pq, v, dist[v]);
            }
        }
    }

    return dist[end];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // ���� ����Ʈ �ʱ�ȭ
    for (int i = 0; i <= n; i++) {
        adj[i] = NULL;
    }

    // ���� ���� �Է�
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

    // ��� ���
    printf("%d\n", dijkstra(1, n, n));

    // �޸� ����
    for (int i = 1; i <= n; i++) {
        Node* current = adj[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }

    return 0;
}