#include <stdio.h>

int n, m, w, b;
char a[101][101];
int check[100][100];
const int dx[] = { -1,0,1,0 }, dy[] = { 0,1,0,-1 };

int dfs(int x, int y, char c) {
	int ret = 1;
	int i, nx, ny;
	check[x][y] = 1;

	for (i = 0; i < 4; i++) {
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx < 0 || nx >= n || ny < 0 || ny >= m)
			continue;
		if (check[nx][ny] != 1 && a[nx][ny] == c)
			ret += dfs(nx, ny, c);
	}
	return ret;
}

int main() {

	int i, j, k;

	scanf("%d %d", &m, &n);
	for (i = 0; i < n; i++)
		scanf("%s", a[i]);

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (check[i][j] != 1) {
				k = dfs(i, j, a[i][j]);
				if (a[i][j] == 'W')
					w += k * k;
				else
					b += k * k;
			}
		}
	}
	printf("%d %d", w, b);

	return 0;
}