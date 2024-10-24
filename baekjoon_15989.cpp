#include<stdio.h>

int main() {
	int dp[10001][4] = { 0, };
	int curN = 0;
	int T, n, i;

	scanf("%d", &T);
	dp[0][1] = 1;
	dp[1][1] = 1;
	for (i = 2; i <= 10000; i++) {
		dp[i][1] = dp[i - 1][1];
		dp[i][2] = dp[i - 2][1] + dp[i - 2][2];
		if (i > 2)
			dp[i][3] = dp[i - 3][1] + dp[i - 3][2] + dp[i - 3][3];
	}
	curN = 3;
	while (T--) {
		scanf("%d", &n);
		printf("%d\n", dp[n][1] + dp[n][2] + dp[n][3]);
	}

	return 0;
}