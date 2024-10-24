#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 987654321

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList;

typedef struct {
    int vertex;
    int dist;
} MinHeapNode;

typedef struct {
    int size;
    int capacity;
    int* pos;
    MinHeapNode** array;
} MinHeap;

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

MinHeapNode* createMinHeapNode(int v, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->vertex = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap* minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}

void dijkstra(AdjList* graph, int n, int src, int* dist) {
    MinHeap* minHeap = createMinHeap(n);

    for (int v = 1; v <= n; ++v) {
        dist[v] = INF;
        minHeap->array[v - 1] = createMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v - 1;
    }

    minHeap->array[src - 1] = createMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src - 1;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = n;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        Node* crawl = graph[u].head;
        while (crawl != NULL) {
            int v = crawl->vertex;

            if (isInMinHeap(minHeap, v) && dist[u] != INF && crawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + crawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            crawl = crawl->next;
        }
    }
}

int main() {
    int n, e, v1, v2;
    scanf("%d %d", &n, &e);

    AdjList graph[805];
    for (int i = 1; i <= n; ++i)
        graph[i].head = NULL;

    for (int i = 0; i < e; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Node* newNode = createNode(b, c);
        newNode->next = graph[a].head;
        graph[a].head = newNode;

        newNode = createNode(a, c);
        newNode->next = graph[b].head;
        graph[b].head = newNode;
    }

    scanf("%d %d", &v1, &v2);

    int dist1[805], dist2[805];
    dijkstra(graph, n, v1, dist1);
    long long int v1_1 = dist1[1];
    long long int v1_v2 = dist1[v2];
    long long int v1_n = dist1[n];

    dijkstra(graph, n, v2, dist2);
    long long int v2_1 = dist2[1];
    long long int v2_n = dist2[n];

    long long int ans1 = v1_1 + v1_v2 + v2_n;
    long long int ans2 = v2_1 + v1_v2 + v1_n;
    long long int ans = ans1 < ans2 ? ans1 : ans2;

    if (ans >= INF) ans = -1;

    printf("%lld\n", ans);

    return 0;
}
