#include<stdio.h>
#include<stdlib.h>
#define Min(a,b) ((a)<(b)?(a):(b))

int main() {
	int H, W, cnt = 0;
	scanf("%d %d", &H, &W);
	int* arr = (int*)calloc(W, sizeof(int));
	for (int i = 0; i < W; i++)
		scanf("%d", &arr[i]);

	int left = 0, right = W - 1, min, start, end;
	while (left < right) {
		min = Min(arr[left], arr[right]);
		start = left + 1;
		end = right;
		while (start < end) {
			if (arr[start] < min) {
				cnt += min - arr[start];
				arr[start] = min;
			}
			start++;
		}
		if (min == arr[left])
			left++;
		else
			right--;
	}
	printf("%d", cnt);
	free(arr);
	return 0;
}