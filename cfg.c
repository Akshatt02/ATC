#include <stdio.h>
#include <string.h>

char input[100];  // Input string
int pos = 0;      // Position pointer

// Function to check S -> aSbb | ε
int S() {
    if (input[pos] == 'a') {  // If 'a' is found
        pos++;  // Move to next character
        if (S()) {  // Recursive call for nested structure
            if (input[pos] == 'b' && input[pos + 1] == 'b') {  // Ensure 2 'b's at the end
                pos += 2;  // Move past 'bb'
                return 1;  // Valid
            }
        }
        return 0;  // Invalid
    }
    return 1;
}

int main() {
    printf("Enter a string: ");
    scanf("%s", input);

    if (S() && input[pos] == '\0')
        printf("Valid string.\n");
    else
        printf("Invalid string.\n");

    return 0;
}
