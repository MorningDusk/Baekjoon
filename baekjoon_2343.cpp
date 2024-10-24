#include <stdio.h>

int max_element(int* list, int size) {
	int i, n = 0;
	for (i = 0; i < size; i++) {
		if (n < list[i])
			n = list[i];
	}
	return n;
}

int main() {

	int n, m, l, r = 0, i;
	int mid, sum, cnt;
	int arr[100001];
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		r += arr[i];
	}
	l = max_element(arr, n);

	while (l <= r) {
		sum = 0;
		cnt = 0;
		mid = (l + r) / 2;
		for (i = 0; i < n; i++) {
			if (sum + arr[i] > mid) {
				sum = 0;
				cnt++;
			}
			sum += arr[i];
		}
		if (sum != 0)
			cnt++;
		if (cnt > m)
			l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%d", l);

	return 0;
}