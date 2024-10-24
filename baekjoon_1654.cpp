#include <stdio.h>
#include <stdlib.h>

int main() {

	int n, k, i, j;
	long long k_max = 0, max_len = 0, cnt;
	long long l, mid, r;
	scanf("%d %d", &k, &n);
	long long *list = (long long*)malloc(sizeof(long long) * k);

	for (i = 0; i < k; i++) {
		scanf("%lld", &list[i]);
		if (list[i] > k_max)
			k_max = list[i];
	}
	l = 1, r = k_max;
	while (l <= r) {
		mid = (l + r) / 2;
		for (j = 0, cnt = 0; j < k; j++) {
			cnt += list[j] / mid;
		}
		if (n <= cnt && max_len < mid)
			max_len = mid;
		if (cnt < n)
			r = mid - 1;
		else
			l = mid + 1;
	}
	printf("%d", max_len);

	return 0;
}