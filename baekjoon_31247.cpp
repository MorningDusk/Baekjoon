#include<stdio.h>

int main() {

	long long T, N, K;
	
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld %lld", &N, &K);
		while (N && K) {
			N /= 2;
			K--;
		}
		printf("%lld\n", (N + 1) / 2);
	}

	return 0;
}