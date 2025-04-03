#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count, n = 0;
char productions[1000][1000];
char first[100], done[100];

int isPresent(char c) {
    for (int i = 0; i < n; i++) {
        if (first[i] == c) return 1;
    }
    return 0;
}

void findfirst(char c, int q1, int q2) {
    if (!isupper(c)) {
        if (!isPresent(c)) {
            first[n++] = c;
        }
        return;
    }

    for (int j = 0; j < count; j++) {
        if (productions[j][0] == c) {
            if (productions[j][2] == '#') {
                if (productions[q1][q2] == '\0') {
                    if (!isPresent('#')) first[n++] = '#';
                }
                else if (productions[q1][q2] != '\0' && (q1 != 0 || q2 != 0)) {
                    findfirst(productions[q1][q2], q1, q2 + 1);
                }
                else {
                    if (!isPresent('#')) first[n++] = '#';
                }
            }
            else if (!isupper(productions[j][2])) {
                if (!isPresent(productions[j][2])) first[n++] = productions[j][2];
            }
            else {
                findfirst(productions[j][2], j, 3);
            }
        }
    }
}

int main() {
    int i, j, ptr = -1;
    char c;

    printf("Enter a number: ");
    scanf("%d", &count);
    getchar();

    printf("Enter Productions: ");
    for (int i = 0; i < count; i++) {
        scanf("%s", productions[i]);
    }

    for (int i = 0; i < count; i++) {
        char c = productions[i][0];

        int found = 0;
        for (int j = 0; j <= ptr; j++) {
            if (done[j] == c) {
                found = 1;
                break;
            }
        }
        if (found) continue;

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
}
