#include <ctype.h>
#include <stdio.h>
#include <string.h>

char production[10][10];
char first[10];
char done[10];
int count, n = 0;

int isPresent(char ch) {
    for (int i = 0; i < n; i++) {
        if (first[i] == ch)
            return 1;
    }
    return 0;
}

void findfirst(char c, int q1, int q2) {
    int j;

    if (!isupper(c)) {
        if (!isPresent(c))
            first[n++] = c;
        return;
    }
    for (j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] == '\0') {
                    if (!isPresent('#'))
                        first[n++] = '#';
                } else if (production[q1][q2] != '\0' && (q1 != 0 || q2 != 0)) {
                    findfirst(production[q1][q2], q1, (q2 + 1));
                } else {
                    if (!isPresent('#'))
                        first[n++] = '#';
                }
            }
            else if (!isupper(production[j][2])) {
                if (!isPresent(production[j][2]))
                    first[n++] = production[j][2];
            }
            else {
                findfirst(production[j][2], j, 3);
            }
        }
    }
}

int main() {
    int i, j, ptr = -1;
    char c;

    printf("Enter the number of productions: ");
    scanf("%d", &count);
    getchar();

    printf("Enter the productions (e.g., A=aB):\n");
    for (i = 0; i < count; i++) {
        printf("Production %d: ", i + 1);
        scanf("%s", production[i]);
    }

    for (i = 0; i < count; i++) {
        c = production[i][0];

        int found = 0;
        for (j = 0; j <= ptr; j++) {
            if (done[j] == c) {
                found = 1;
                break;
            }
        }
        if (found)
            continue;

        ptr++;
        done[ptr] = c;
        n = 0;

        findfirst(c, 0, 0);

        printf("First(%c) = { ", c);
        for (j = 0; j < n; j++) {
            printf("%c", first[j]);
            if (j < n - 1)
                printf(", ");
        }
        printf(" }\n");
    }

    return 0;
}