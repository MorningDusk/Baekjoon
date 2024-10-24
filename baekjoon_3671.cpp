#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX 10000000

int num[MAX], len;
bool check[7];
int v[7], ans[7];
bool s[MAX];
char str[8];

void cal() {
    for (int i = 2; i < MAX; i++)
        num[i] = i;
    for (int i = 2; i <= sqrt(MAX); i++) {
        if (num[i] == 0) continue;
        for (int j = i + i; j < MAX; j += i)
            num[j] = 0;
    }
}

void dfs(int idx, int length) {
    if (idx == length) {
        char ss[8] = "";
        for (int i = 0; i < idx; i++)
            ss[i] = ans[i] + '0';
        int val = atoi(ss);
        if (num[val] != 0)
            s[val] = true;
        return;
    }

    for (int i = 0; i < strlen(str); i++) {
        if (check[i]) continue;
        ans[idx] = v[i];
        check[i] = true;
        dfs(idx + 1, length);
        check[i] = false;
    }
}

int main() {
    cal();
    int test;
    scanf("%d", &test);
    for (int t = 0; t < test; t++) {
        memset(v, 0, sizeof(v));
        memset(s, false, sizeof(s));
        scanf("%s", str);
        len = strlen(str);
        for (int j = 0; j < len; j++) {
            check[j] = false;
            int val = str[j] - '0';
            v[j] = val;
        }
        for (int j = 1; j <= len; j++) {
            memset(ans, 0, sizeof(ans));
            dfs(0, j);
        }
        int count = 0;
        for (int i = 0; i < MAX; i++) {
            if (s[i]) count++;
        }
        printf("%d\n", count);
    }
    return 0;
}
