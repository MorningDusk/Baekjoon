#include <stdio.h>
#include <stdlib.h>

int FindElement(int* list, int key, int l, int r) {
	int mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (key < list[mid])
			r = mid - 1;
		else if (key > list[mid])
			l = mid + 1;
		else if (key == list[mid])
			return 1;
	}
	return 0;
}

int main() {

	int n, m, i, cnt = 0, key;
	scanf("%d %d", &n, &m);

	int *a = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);

	for (i = 0; i < m; i++) {
		scanf("%d", &key);
		cnt += FindElement(a, key, 0, n - 1);
	}
	printf("%d", n + m - cnt * 2);

	return 0;
}