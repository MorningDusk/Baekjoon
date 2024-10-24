#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAX_N 100001

typedef struct {
    int v;
    long long B;
} Edge;

typedef struct {
    Edge edges[MAX_N];
    int size;
} AdjacencyList;

AdjacencyList adj[MAX_N];
long long A[MAX_N];
int N, M;
long long K;

int main() {
    scanf("%d %d %lld", &N, &M, &K);

    for (int i = 1; i <= N; i++) {
        scanf("%lld", &A[i]);
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        long long B;
        scanf("%d %d %lld", &u, &v, &B);
        adj[u].edges[adj[u].size].v = v;
        adj[u].edges[adj[u].size].B = B;
        adj[u].size++;
    }

    int u = 1;
    long long c = 0;
    long long step = 0;

    int visited[MAX_N] = { 0 };
    int cycle_start = 0, cycle_length = 0;
    long long cycle_c_sum = 0;

    while (step < K) {
        int next_u = -1;
        long long max_B = -1;

        for (int i = 0; i < adj[u].size; i++) {
            if (c >= adj[u].edges[i].B && adj[u].edges[i].B > max_B) {
                next_u = adj[u].edges[i].v;
                max_B = adj[u].edges[i].B;
            }
        }

        if (next_u == -1) break;

        step++;
        c = (c + A[next_u]) % MOD;
        u = next_u;

        if (visited[u]) {
            cycle_start = visited[u];
            cycle_length = step - cycle_start;
            cycle_c_sum = c;
            break;
        }

        visited[u] = step;
    }

    if (cycle_length > 0) {
        long long remaining_steps = K - step;
        long long cycle_repeats = remaining_steps / cycle_length;
        long long cycle_remainder = remaining_steps % cycle_length;

        c = (c + cycle_repeats * cycle_c_sum) % MOD;

        for (int i = 0; i < cycle_remainder; i++) {
            int next_u = -1;
            long long max_B = -1;

            for (int j = 0; j < adj[u].size; j++) {
                if (c >= adj[u].edges[j].B && adj[u].edges[j].B > max_B) {
                    next_u = adj[u].edges[j].v;
                    max_B = adj[u].edges[j].B;
                }
            }

            if (next_u == -1) break;

            c = (c + A[next_u]) % MOD;
            u = next_u;
        }
    }

    printf("%d %lld\n", u, c);

    return 0;
}
