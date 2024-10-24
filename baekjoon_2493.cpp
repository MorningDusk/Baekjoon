#include <stdio.h>
#include <stdlib.h>

typedef struct TOWER {
	int index, height;
}Tower;

typedef struct STACK {
	Tower* data;
	int size, capacity;
}Stack;

Stack* createStack(int capacity) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->data = (Tower*)malloc(capacity * sizeof(Tower));
	stack->size = 0;
	stack->capacity = capacity;
	return stack;
}

int isEmpty(Stack* stack) {
	return stack->size == 0;
}

Tower top(Stack* stack) {
	return stack->data[stack->size - 1];
}

void push(Stack* stack, int index, int height) {
	Tower tower = { index, height };
	stack->data[stack->size++] = tower;
}

void pop(Stack* stack) {
	if (!isEmpty(stack))
		stack->size--;
}

void freeStack(Stack* stack) {
	free(stack->data);
	free(stack);
}

int main() {
	int num, height;
	scanf("%d", &num);

	Stack* stack = createStack(num);
	for (int i = 0; i < num; i++) {
		scanf("%d", &height);
		while (!isEmpty(stack)) {
			if (height < top(stack).height) {
				printf("%d ", top(stack).index);
				break;
			}
			pop(stack);
		}
		if (isEmpty(stack))
			printf("0 ");
		push(stack, i + 1, height);
	}
	freeStack(stack);
	return 0;
}