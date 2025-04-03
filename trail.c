#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_NONTERM 10   // maximum number of nonterminals
#define MAX_PROD 10      // maximum number of alternatives per nonterminal
#define MAX_LEN 21       // maximum length of a production alternative

typedef struct {
    char symbol;                   // nonterminal (e.g. 'S', 'A', etc.)
    char productions[MAX_PROD][MAX_LEN]; // list of alternatives for this nonterminal
    int count;                     // number of alternatives stored
} NonTerminal;

NonTerminal nonTerminals[MAX_NONTERM];
int nonTerminalCount = 0;

// Helper: returns index in nonTerminals array for a given nonterminal symbol
int findNonTerminalIndex(char symbol) {
    for (int i = 0; i < nonTerminalCount; i++) {
        if (nonTerminals[i].symbol == symbol)
            return i;
    }
    return -1;
}

// This function adds productions for a nonterminal.
// The input string (prodStr) is assumed to be the part after "->"
// and may contain alternatives separated by '|'.
void addProduction(char lhs, char* prodStr) {
    int index = findNonTerminalIndex(lhs);
    if (index == -1) {
        index = nonTerminalCount;
        nonTerminals[nonTerminalCount].symbol = lhs;
        nonTerminals[nonTerminalCount].count = 0;
        nonTerminalCount++;
    }
    // Use strtok to split alternatives separated by '|'
    char *token = strtok(prodStr, "|");
    while (token != NULL) {
        strcpy(nonTerminals[index].productions[nonTerminals[index].count], token);
        nonTerminals[index].count++;
        token = strtok(NULL, "|");
    }
}

int main() {
    int n;
    char prodInput[50];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    // Read productions from the user
    for (int i = 0; i < n; i++) {
        printf("Enter production %d: ", i + 1);
        scanf("%s", prodInput);
        // Expected format: A->...   (no spaces)
        char lhs = prodInput[0];
        // Skip the "->" (at positions 1 and 2)
        char alternatives[50];
        strcpy(alternatives, prodInput + 3);
        addProduction(lhs, alternatives);
    }

    // Compute nullable for each nonterminal.
    // A nonterminal is nullable if one of its alternatives is "ε"
    // or if every symbol in an alternative is nullable.
    bool nullable[MAX_NONTERM] = { false };
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < nonTerminalCount; i++) {
            if (nullable[i])
                continue;
            for (int j = 0; j < nonTerminals[i].count; j++) {
                char *prod = nonTerminals[i].productions[j];
                // If the production is exactly "ε", mark nullable.
                if (strcmp(prod, "ε") == 0) {
                    nullable[i] = true;
                    change = true;
                    break;
                }
                bool allNullable = true;
                int len = strlen(prod);
                for (int k = 0; k < len; k++) {
                    char symbol = prod[k];
                    if (isupper(symbol)) { // nonterminal
                        int idx = findNonTerminalIndex(symbol);
                        if (idx == -1 || !nullable[idx]) {
                            allNullable = false;
                            break;
                        }
                    } else {
                        // Terminal symbols (other than ε) are not nullable.
                        allNullable = false;
                        break;
                    }
                }
                if (allNullable) {
                    nullable[i] = true;
                    change = true;
                    break;
                }
            }
        }
    }

    // Compute trailing sets.
    // For each nonterminal, we use an array (indexed by ASCII code) to mark the presence
    // of terminal symbols in its trailing set.
    bool trailing[MAX_NONTERM][128] = { false };

    // Fixed point algorithm: For every production alternative for each nonterminal,
    // scan the alternative from right to left.
    // When a terminal is encountered it is added directly;
    // when a nonterminal is encountered, its trailing set is unioned.
    // If the nonterminal is nullable, the scan continues to the next symbol.
    bool updated = true;
    while (updated) {
        updated = false;
        for (int i = 0; i < nonTerminalCount; i++) {
            for (int j = 0; j < nonTerminals[i].count; j++) {
                char *prod = nonTerminals[i].productions[j];
                int len = strlen(prod);
                bool flag = true;  // flag indicates whether the preceding symbol can affect trailing
                for (int k = len - 1; k >= 0 && flag; k--) {
                    char symbol = prod[k];
                    if (symbol == 'ε') {
                        // ε-production: nothing to add
                        continue;
                    }
                    if (isupper(symbol)) { // nonterminal
                        int idx = findNonTerminalIndex(symbol);
                        if (idx != -1) {
                            // Union trailing set of this nonterminal into trailing of the LHS
                            for (int t = 0; t < 128; t++) {
                                if (trailing[idx][t] && !trailing[i][t]) {
                                    trailing[i][t] = true;
                                    updated = true;
                                }
                            }
                            // If the nonterminal is not nullable, stop scanning further left.
                            if (!nullable[idx])
                                flag = false;
                        }
                    } else { // terminal
                        if (!trailing[i][(int)symbol]) {
                            trailing[i][(int)symbol] = true;
                            updated = true;
                        }
                        flag = false;
                    }
                }
            }
        }
    }

    // Display the computed trailing sets.
    printf("\nTrailing sets:\n");
    for (int i = 0; i < nonTerminalCount; i++) {
        printf("Trailing(%c) = { ", nonTerminals[i].symbol);
        bool first = true;
        for (int t = 0; t < 128; t++) {
            if (trailing[i][t]) {
                if (!first)
                    printf(", ");
                printf("%c", t);
                first = false;
            }
        }
        printf(" }\n");
    }

    return 0;
}