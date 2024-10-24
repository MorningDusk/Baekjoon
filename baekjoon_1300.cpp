#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}

int main() {

	int n, k, i;
	int f = 1, l, m, res = 0;
	scanf("%d %d", &n, &k);
	l = k;

	while (1) {
		if (f > l)
			break;
		m = (f + l) / 2;

		int cnt = 0;
		for (i = 1; i <= n; i++)
			cnt += min(n, m / i);
		
		if (cnt >= k) {
			res = m;
			l = m - 1;
		}
		else
			f = m + 1;
	}
	printf("%d", res);

	return 0;
}