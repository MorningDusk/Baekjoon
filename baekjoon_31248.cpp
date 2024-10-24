#include<stdio.h>

typedef struct p {
	char first, second;
}P;

int moveCnt = 0;
P moves[20];

void move(char start, char end) {
	moves[moveCnt].first = start;
	moves[moveCnt].second = end;
	moveCnt++;
}

void hanoi(int n, char now, char next, char tmp) {
	if (n == 1) {
		move(now, next);
		return;
	}
	hanoi(n - 1, now, tmp, next);
	move(now, next);
	hanoi(n - 1, tmp, next, now);
}

void modHanoi(int n, char now, char next, char tail, char dest) {
	if (n == 1) {
		move(now, dest);
		return;
	}
	else if (n == 2) {
		move(now, next);
		move(now, dest);
		move(next, dest);
		return;
	}
	hanoi(n - 2, now, next, tail);
	move(now, tail);
	move(now, dest);
	move(tail, dest);
	modHanoi(n - 2, next, now, tail, dest);
}

int main() {

	int N, i;
	scanf("%d", &N);
	modHanoi(N, 'A', 'B', 'C', 'D');
	printf("%d\n", moveCnt);
	for (i = 0; i < moveCnt; i++) {
		printf("%c %c\n", moves[i].first, moves[i].second);
	}
	return 0;
}