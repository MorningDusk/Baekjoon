#include <stdio.h>
#include <stdlib.h>

int getLength(const char* str) {
	int len = 0;
	while (str[len])
		len++;
	return len;
}

void reverseString(char* str, int len) {
	for (int i = 0; i < len/2; i++) {
		char temp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = temp;
	}
}

int canTransform(char* s, char* t) {
	int slen = getLength(s);
	int tlen = getLength(t);

	int currentLen = tlen;
	char* current = (char*)malloc(sizeof(char) * (tlen + 1));

	for (int i = 0; i <= tlen; i++)
		current[i] = t[i];

	while (currentLen > slen) {
		if (current[currentLen - 1] == 'A') {
			current[currentLen - 1] = '\0';
			currentLen--;
		}
		else if (current[currentLen - 1] == 'B') {
			current[currentLen - 1] = '\0';
			currentLen--;
			reverseString(current, currentLen);
		}
		else {
			free(current);
			return 0;
		}
	}

	int result = 1;
	for (int i = 0; i < slen; i++) {
		if (current[i] != s[i]) {
			result = 0;
			break;
		}
	}

	free(current);
	return result;
}

int main() {
	char s[50], t[51];
	scanf("%s", s);
	scanf("%s", t);

	printf("%d\n", canTransform(s, t));

	return 0;
}