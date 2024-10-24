#include<stdio.h>

int N, M;
int ans;
int MAP[501][501];
int visited[501][501];

int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };

int carBlock(int y, int x) {
	int ans = MAP[y][x];
	int max = ans;
	if (x + 2 < M) { //ぬ
		if (y + 1 < N) {
			ans += MAP[y + 1][x + 1] + MAP[y][x + 1] + MAP[y][x + 2];
			max = ans > max ? ans : max;
		}
		if (y - 1 >= 0) { //で
			ans = MAP[y][x] + MAP[y - 1][x + 1] + MAP[y][x + 1] + MAP[y][x + 2];
			max = ans > max ? ans : max;
		}
	}
	if (y + 2 < N) {
		if (x - 1 >= 0) { //っ
			ans = MAP[y][x] + MAP[y + 1][x - 1] + MAP[y + 1][x] + MAP[y + 2][x];
			max = ans > max ? ans : max;
		}
		if (x + 1 < M) { //た
			ans = MAP[y][x] + MAP[y + 1][x] + MAP[y + 2][x] + MAP[y + 1][x + 1];
			max = ans > max ? ans : max;
		}
	}
	return max;
}

int makeBlock(int y, int x, int n, int sum) {
	if (n == 0) {
		if (ans < sum)
			ans = sum;
		return 0;
	}
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= N || ny < 0 || nx < 0 || nx >= M)
			continue;
		if (!visited[ny][nx]) {
			visited[ny][nx] = 1;
			makeBlock(ny, nx, n - 1, sum + MAP[ny][nx]);
			visited[ny][nx] = 0;
		}
	}
	return 0;
}

int sol() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = 1;
			makeBlock(i, j, 4 - 1, MAP[i][j]);
			visited[i][j] = 0;
			int tmp = carBlock(i, j);
			ans = ans > tmp ? ans : tmp;
		}
	}
	return 0;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			scanf("%d", &MAP[i][j]);
	}
	sol();
	printf("%d", ans);
}