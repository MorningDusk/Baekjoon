#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l, r;
} Interval;

// 두 구간의 교집합을 구하는 함수
void findIntersection(int* left, int* right, int l1, int r1, int l2, int r2) {
    *left = (l1 > l2) ? l1 : l2;
    *right = (r1 < r2) ? r1 : r2;
}

// 구간 조합의 교집합을 구하는 함수
void getIntersectionOfSelected(Interval* intervals, int* selected, int selected_count, int* result_l, int* result_r) {
    *result_l = intervals[selected[0]].l;
    *result_r = intervals[selected[0]].r;

    for (int i = 1; i < selected_count; i++) {
        findIntersection(result_l, result_r, *result_l, *result_r,
            intervals[selected[i]].l, intervals[selected[i]].r);
    }
}

// 조합을 생성하는 재귀 함수
int findMinIntervals(Interval* intervals, int N, int target_l, int target_r,
    int current_idx, int* selected, int selected_count) {
    if (current_idx > N) return -1;

    // 현재 선택된 구간들의 교집합 확인
    if (selected_count > 0) {
        int intersection_l, intersection_r;
        getIntersectionOfSelected(intervals, selected, selected_count, &intersection_l, &intersection_r);

        // 정확히 target 구간과 일치하는 경우
        if (intersection_l == target_l && intersection_r == target_r) {
            return selected_count;
        }

        // 교집합이 target 구간보다 작아진 경우 더 이상 진행할 필요 없음
        if (intersection_l > target_l || intersection_r < target_r) {
            return -1;
        }
    }

    if (current_idx == N) return -1;

    int min_count = -1;

    // 현재 구간을 선택하는 경우
    selected[selected_count] = current_idx;
    int with_current = findMinIntervals(intervals, N, target_l, target_r,
        current_idx + 1, selected, selected_count + 1);

    // 현재 구간을 선택하지 않는 경우
    int without_current = findMinIntervals(intervals, N, target_l, target_r,
        current_idx + 1, selected, selected_count);

    // 최소값 계산
    if (with_current != -1 && (min_count == -1 || with_current < min_count))
        min_count = with_current;
    if (without_current != -1 && (min_count == -1 || without_current < min_count))
        min_count = without_current;

    return min_count;
}

int main() {
    int N, Q;
    scanf("%d", &N);

    Interval* intervals = (Interval*)malloc(N * sizeof(Interval));
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &intervals[i].l, &intervals[i].r);
    }

    scanf("%d", &Q);

    int* selected = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < Q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);

        int result = findMinIntervals(intervals, N, l, r, 0, selected, 0);
        printf("%d\n", result);
    }

    free(intervals);
    free(selected);

    return 0;
}