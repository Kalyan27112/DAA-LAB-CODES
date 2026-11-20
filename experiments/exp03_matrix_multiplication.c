#include <stdio.h>
#include <limits.h>

#define MAX 20

void printOptimalParens(int s[MAX][MAX], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

void matrixChainOrder(int p[], int n) {
    int m[MAX][MAX] = {0};
    int s[MAX][MAX] = {0};

    // Cost is 0 for a single matrix
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // L is chain length from 2 to n
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            // Try every split point k between i and j - 1
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]);
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\n--- Minimum Cost Table m[i][j] ---\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i)
                printf("    -\t");
            else
                printf("%5d\t", m[i][j]);
        }
        printf("\n");
    }

    printf("\n--- Split Point Table s[i][j] ---\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j <= i)
                printf("    -\t");
            else
                printf("%5d\t", s[i][j]);
        }
        printf("\n");
    }

    printf("\nMinimum number of scalar multiplications: %d\n", m[1][n]);
    printf("Optimal Parenthesization: ");
    printOptimalParens(s, 1, n);
    printf("\n");
}

int main() {
    int n, p[MAX];

    printf("Enter number of matrices: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX) {
        printf("Invalid number of matrices.\n");
        return 1;
    }

    printf("Enter %d dimensions (p0 p1 ... pn): ", n + 1);
    for (int i = 0; i <= n; i++) {
        if (scanf("%d", &p[i]) != 1 || p[i] <= 0) {
            printf("Invalid dimension.\n");
            return 1;
        }
    }

    matrixChainOrder(p, n);
    return 0;
}
