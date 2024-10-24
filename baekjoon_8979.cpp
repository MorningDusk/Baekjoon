#include<stdio.h>
#include<stdlib.h>

struct Medal {
	int country, gold, silver, bronze;
};

int main() {

	int n, k;
	scanf("%d %d", &n, &k);

	struct Medal* medals = (struct Medal*)malloc(n * sizeof(struct Medal));
	int target = 0;
	int rank = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &medals[i].country, &medals[i].gold, &medals[i].silver, &medals[i].bronze);

		if (medals[i].country == k)
			target = i;
	}

	for (int i = 0; i < n; i++) {
		if (i != target) {
			if (medals[i].gold > medals[target].gold)
				rank++;
			else if (medals[i].gold == medals[target].gold) {
				if (medals[i].silver > medals[target].silver)
					rank++;
				else if (medals[i].silver == medals[target].silver) {
					if (medals[i].bronze > medals[target].bronze)
						rank++;
				}
			}
		}
	}
	printf("%d", rank + 1);
}