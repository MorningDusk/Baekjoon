#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 10001
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int* arr;
    int size;
} Vector;

void initVector(Vector* vec) {
    vec->arr = (int*)malloc(MAX_LEN * sizeof(int));
    vec->size = 0;
}

void clearVector(Vector* vec) {
    vec->size = 0;
}

void pushBack(Vector* vec, int value) {
    vec->arr[vec->size++] = value;
}

void freeVector(Vector* vec) {
    free(vec->arr);
}

int main() {
    int T;
    scanf("%d", &T);

    Vector vecList[26];
    for (int i = 0; i < 26; i++) {
        initVector(&vecList[i]);
    }

    char W[MAX_LEN];
    for (int test_case = 1; test_case <= T; test_case++) {
        int K;
        scanf("%s %d", W, &K);

        // 초기화
        int mini = 100000;
        int maxi = 0;
        for (int i = 0; i < 26; i++) {
            clearVector(&vecList[i]);
        }

        // 문자열 길이 계산
        int len = 0;
        while (W[len]) len++;

        // 각 문자의 인덱스 저장
        for (int i = 0; i < len; i++) {
            int num = W[i] - 'a';
            pushBack(&vecList[num], i);
        }

        // 각 알파벳에 대해 검사
        for (int i = 0; i < 26; i++) {
            int vsize = vecList[i].size;
            if (vsize >= K) {
                for (int j = 0; j <= vsize - K; j++) {
                    int currLen = vecList[i].arr[j + K - 1] - vecList[i].arr[j] + 1;
                    mini = MIN(mini, currLen);
                    maxi = MAX(maxi, currLen);
                }
            }
        }

        if (mini == 100000 || maxi == 0) {
            printf("-1\n");
        }
        else {
            printf("%d %d\n", mini, maxi);
        }
    }

    // 메모리 해제
    for (int i = 0; i < 26; i++) {
        freeVector(&vecList[i]);
    }

    return 0;
}