#include<stdio.h>

long long sum[1025][1025];

int main() {
	int n, m, x1, x2, y1, y2, num;
	long long ans;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &num);
			if (i == 1)
				sum[i][j] = sum[i][j - 1] + num;
			else if (j == 1)
				sum[i][j] = sum[i - 1][j] + num;
			else
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + num;
		}
	}

	while (m--) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		ans = sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
		printf("%lld\n", ans);
	}
	return 0;
}