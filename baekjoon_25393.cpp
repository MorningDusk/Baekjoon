#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l, r;
} Interval;

// �� ������ �������� ���ϴ� �Լ�
void findIntersection(int* left, int* right, int l1, int r1, int l2, int r2) {
    *left = (l1 > l2) ? l1 : l2;
    *right = (r1 < r2) ? r1 : r2;
}

// ���� ������ �������� ���ϴ� �Լ�
void getIntersectionOfSelected(Interval* intervals, int* selected, int selected_count, int* result_l, int* result_r) {
    *result_l = intervals[selected[0]].l;
    *result_r = intervals[selected[0]].r;

    for (int i = 1; i < selected_count; i++) {
        findIntersection(result_l, result_r, *result_l, *result_r,
            intervals[selected[i]].l, intervals[selected[i]].r);
    }
}

// ������ �����ϴ� ��� �Լ�
int findMinIntervals(Interval* intervals, int N, int target_l, int target_r,
    int current_idx, int* selected, int selected_count) {
    if (current_idx > N) return -1;

    // ���� ���õ� �������� ������ Ȯ��
    if (selected_count > 0) {
        int intersection_l, intersection_r;
        getIntersectionOfSelected(intervals, selected, selected_count, &intersection_l, &intersection_r);

        // ��Ȯ�� target ������ ��ġ�ϴ� ���
        if (intersection_l == target_l && intersection_r == target_r) {
            return selected_count;
        }

        // �������� target �������� �۾��� ��� �� �̻� ������ �ʿ� ����
        if (intersection_l > target_l || intersection_r < target_r) {
            return -1;
        }
    }

    if (current_idx == N) return -1;

    int min_count = -1;

    // ���� ������ �����ϴ� ���
    selected[selected_count] = current_idx;
    int with_current = findMinIntervals(intervals, N, target_l, target_r,
        current_idx + 1, selected, selected_count + 1);

    // ���� ������ �������� �ʴ� ���
    int without_current = findMinIntervals(intervals, N, target_l, target_r,
        current_idx + 1, selected, selected_count);

    // �ּҰ� ���
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