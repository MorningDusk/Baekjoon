#include<stdio.h>
#include<stdlib.h>

int main() {

	long long i, j, tmp, N, K, a, b;
	
	scanf("%lld %lld", &N, &K);
	long long* min = (long long*)malloc(N * sizeof(long long));
	for (i = 0; i < N; i++) {
		scanf("%lld %lld", &a, &b);
		min[i] = b - a;
	}

	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			if (min[i] > min[j]) {
				tmp = min[i];
				min[i] = min[j];
				min[j] = tmp;
			}
		}
	}

	if (min[K - 1] < 0)
		printf("0");
	else
		printf("%lld", min[K - 1]);
	
	return 0;
}