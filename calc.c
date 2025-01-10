#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function prototypes
char *add(const char *a, const char *b);
char *subtract(const char *a, const char *b);
char *multiply(const char *a, const char *b);
char *divide(const char *a, const char *b);
char *modulus(const char *a, const char *b);
char *power(const char *a, const char *b);
char *factorial(const char *a);
int is_number(const char *str);

// REPL (interactive prompt)
void repl() {
    char input[256];
    printf("Arbitrary Precision Calculator\n");
    printf("Enter operations (e.g., '123 + 456') or 'exit' to quit.\n");

    while (1) {
        printf(">> ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        // Exit condition
        if (strcmp(input, "exit") == 0) break;

        // Parse input
        char op;
        char num1[128], num2[128];
        if (sscanf(input, "%s %c %s", num1, &op, num2) < 2) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (!is_number(num1) || (op != '!' && !is_number(num2))) {
            printf("Invalid numbers. Try again.\n");
            continue;
        }

        char *result = NULL;

        // Perform the operation
        switch (op) {
            case '+': result = add(num1, num2); break;
            case '-': result = subtract(num1, num2); break;
            case '*': result = multiply(num1, num2); break;
            case '/': result = divide(num1, num2); break;
            case '%': result = modulus(num1, num2); break;
            case '^': result = power(num1, num2); break;
            case '!': result = factorial(num1); break;
            default:
                printf("Unknown operator '%c'. Try again.\n", op);
                continue;
        }

        // Print the result
        if (result) {
            printf("Result: %s\n", result);
            free(result); // Free memory allocated for the result
        }
    }
    printf("Goodbye!\n");
}

// Function to check if a string is a valid number
int is_number(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

// Function to add two large numbers
char *add(const char *a, const char *b) {
    int len1 = strlen(a), len2 = strlen(b);
    int max_len = len1 > len2 ? len1 : len2;
    char *result = (char *)malloc(max_len + 2); // +1 for carry, +1 for null terminator

    int carry = 0, sum, i, j, k = max_len;
    result[k + 1] = '\0';

    for (i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0 || carry; i--, j--, k--) {
        int digit1 = (i >= 0) ? a[i] - '0' : 0;
        int digit2 = (j >= 0) ? b[j] - '0' : 0;

        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[k] = (sum % 10) + '0';
    }
    return strdup(&result[k + 1]);
}

// Function to subtract two large numbers
char *subtract(const char *a, const char *b) {
    // Assume a >= b for simplicity
    int len1 = strlen(a), len2 = strlen(b);
    char *result = (char *)malloc(len1 + 1); // Enough space for result
    int borrow = 0, diff, i, j, k = len1 - 1;

    result[len1] = '\0';

    for (i = len1 - 1, j = len2 - 1; i >= 0; i--, j--, k--) {
        int digit1 = a[i] - '0';
        int digit2 = (j >= 0) ? b[j] - '0' : 0;

        diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[k] = diff + '0';
    }

    // Remove leading zeros
    for (i = 0; result[i] == '0' && result[i + 1]; i++);
    return strdup(&result[i]);
}

// Function to multiply two large numbers
char *multiply(const char *a, const char *b) {
    int len1 = strlen(a), len2 = strlen(b);
    int *temp = (int *)calloc(len1 + len2, sizeof(int));
    char *result = (char *)malloc(len1 + len2 + 1);

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            temp[i + j + 1] += (a[i] - '0') * (b[j] - '0');
            temp[i + j] += temp[i + j + 1] / 10;
            temp[i + j + 1] %= 10;
        }
    }

    // Convert temp array to string
    int k = 0, leading_zero = 1;
    for (int i = 0; i < len1 + len2; i++) {
        if (leading_zero && temp[i] == 0) continue;
        leading_zero = 0;
        result[k++] = temp[i] + '0';
    }
    result[k] = '\0';

    free(temp);
    return k ? result : strdup("0");
}

// Function to divide two large numbers (integer division)
char *divide(const char *a, const char *b) {
    // Not implemented for simplicity
    return strdup("Division not implemented");
}

// Function to calculate modulus of two numbers
char *modulus(const char *a, const char *b) {
    // Not implemented for simplicity
    return strdup("Modulus not implemented");
}

// Function to calculate a^b
char *power(const char *a, const char *b) {
    // Not implemented for simplicity
    return strdup("Power not implemented");
}

// Function to calculate factorial
char *factorial(const char *a) {
    char *result = strdup("1");
    char *temp, *counter = strdup("1");

    while (strcmp(counter, a) <= 0) {
        temp = multiply(result, counter);
        free(result);
        result = temp;

        // Increment counter
        char *increment = add(counter, "1");
        free(counter);
        counter = increment;
    }

    free(counter);
    return result;
}

// Main function
int main() {
    repl();
    return 0;
}