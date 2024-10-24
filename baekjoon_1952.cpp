#include<stdio.h>

int main() {
	int visited[100][100] = { 0 };
	int dx[] = { 0,1,0,-1 };
	int dy[] = { 1,0,-1,0 };
	int m, n;
	int x = 0, y = 0, dir = 0, ans = 0;

	scanf("%d %d", &m, &n);
	while (1) {
		if (visited[x][y] == 1) {
			printf("%d", ans - 1);
			return 0;
		}
		visited[x][y] = 1;
		int nextX = x + dx[dir];
		int nextY = y + dy[dir];
		if (nextX < 0 || nextY < 0 || nextX >= m || nextY >= n || visited[nextX][nextY]) {
			dir = (dir + 1) % 4;
			nextX = x + dx[dir];
			nextY = y + dy[dir];
			ans++;
		}
		x = nextX;
		y = nextY;
	}

	return 0;
}