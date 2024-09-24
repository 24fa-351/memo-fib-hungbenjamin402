#include <stdio.h>
#include <stdlib.h>  // For atoi()
#include <stdint.h>  // For uintmax_t
#include <string.h>  // For strcmp()

#define MAX_N 1000000  // Maximum value for N

// Function prototypes
uintmax_t fib_r(int n);
uintmax_t fib_r_core(int n);
uintmax_t fib_i(int n);
uintmax_t fib_i_core(int n);

// Memoization arrays
uintmax_t memo_rec[MAX_N];
uintmax_t memo_iter[MAX_N];

// Recursive Fibonacci function (core)
uintmax_t fib_r_core(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 0;
    if (n == 2) return 1;
    return fib_r(n - 1) + fib_r(n - 2);
}

// Memoized recursive Fibonacci function
uintmax_t fib_r(int n) {
    if (n < 0) return 0;  // Handle invalid input
    if (n < MAX_N && memo_rec[n] != UINTMAX_MAX) {
        return memo_rec[n];
    }

    uintmax_t result = fib_r_core(n);

    if (n < MAX_N) {
        memo_rec[n] = result;
    }
    return result;
}

// Iterative Fibonacci function (core)
uintmax_t fib_i_core(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 0;
    if (n == 2) return 1;

    uintmax_t a = 0, b = 1, c;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Memoized iterative Fibonacci function
uintmax_t fib_i(int n) {
    if (n < 0) return 0;  // Handle invalid input
    if (n < MAX_N && memo_iter[n] != UINTMAX_MAX) {
        return memo_iter[n];
    }

    uintmax_t result = fib_i_core(n);

    if (n < MAX_N) {
        memo_iter[n] = result;
    }
    return result;
}

int main(int argc, char *argv[]) {
    // Initialize memoization arrays
    for (int i = 0; i < MAX_N; i++) {
        memo_rec[i] = UINTMAX_MAX;
        memo_iter[i] = UINTMAX_MAX;
    }

    int N;
    char method = 'r';  // Default to recursive method

    if (argc == 2 || argc == 3) {
        N = atoi(argv[1]);
        if (argc == 3) {
            method = argv[2][0];
        }
    } else if (argc == 4) {
        N = atoi(argv[1]);
        method = argv[2][0];
        
        // Read integer from the file
        FILE *fpointer = fopen(argv[3], "r");
        if (fpointer == NULL) {
            printf("Error opening file\n");
            return -1;
        }

        int fileInteger = 0;
        fscanf(fpointer, "%d", &fileInteger);
        fclose(fpointer);

        N += fileInteger;
    } else {
        printf("Usage: %s <integer> [r/i] [filename]\n", argv[0]);
        return 1;
    }

    // Calculate Fibonacci using specified method
    uintmax_t result;

    if (method == 'i') {
        result = fib_i(N);
    } else if (method == 'r') {
        result = fib_r(N);
    } else {
        printf("Invalid method. Use 'r' for recursive or 'i' for iterative.\n");
        return 1;
    }

    // Output the result
    printf("%ju", result);

    return 0;
}