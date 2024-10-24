#include <stdio.h>

int main() {

	int n, i, tmp, num;
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		tmp = i;
		num = i;

		while (tmp > 0) {
			num += tmp % 10;
			tmp /= 10;
		}

		if (num == n) {
			printf("%d", i);
			n = 0;
			break;
		}
	}
	if (n != 0)
		printf("0");
}