#include <cstdio>

int n, i;
char a[22], s[22];

int main() {

    scanf("%d", &n); 
    n *= 2;
    
    for (n--; n--;) {
        scanf("%s", s);
        for (i = 0; s[i]; i++)
            a[i] ^= s[i];
    }

    printf("%s", a);
    return 0;
}