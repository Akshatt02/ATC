#include <stdio.h>
#include <string.h>
#include <ctype.h>

int nop, m = 0;
char prod[10][10], res[10];
int visited[256] = {0}; 

void FIRST(char c);
void FOLLOW(char c);
void result(char c);

int main() {
    int i;
    char c;

    printf("Enter the no. of productions : ");
    scanf("%d", &nop);

    for (i = 0; i < nop; ++i) {
        printf("Enter production Number %d : ", i + 1);
        scanf("%s", prod[i]);
    }

    printf("\nFOLLOW sets:\n");
    for (i = 0; i < nop; ++i) 
    {
        c = prod[i][0];
        if (isupper(c) && !visited[c])
        {
            visited[c] = 1;
            m = 0;
            memset(res, '\0', sizeof(res));
            FOLLOW(c);

            printf("Follow(%c) = { ", c);
            for (int j = 0; j < m; ++j) {
                printf("%c ", res[j]);
                if (j < m - 1)
                    printf(", ");
            }
            puts("}");
        }
    }

    return 0;
}

void FOLLOW(char c) 
{
    int i, j;
    if (prod[0][0] == c)
        result('$');
    for (i = 0; i < nop; ++i)
    {
        for (j = 2; j <= strlen(prod[i]); ++j)
        {
            if (prod[i][j] == c)
            {
                if (prod[i][j + 1] != '\0')
                    FIRST(prod[i][j + 1]);
                if (prod[i][j + 1] == '\0' && c != prod[i][0]) 
                    FOLLOW(prod[i][0]);
            }
        }
    }
    return;
}

void FIRST(char c)
{
    int k;
    if (!(isupper(c)))
        result(c);
    for (k = 0; k < nop; ++k)
    {
        if (prod[k][0] == c)
        {
            if (prod[k][2] == '#')
                FOLLOW(prod[k][0]);
            else if (prod[k][2] == c)
                return;
            else if (islower(prod[k][2]))
                result(prod[k][2]);
            else
                FIRST(prod[k][2]);
        }
    }
    return;
}

void result(char c)
{
    int i;
    for (i = 0; i <= m; ++i)
        if (res[i] == c)
            return;
    res[m++] = c;
}
