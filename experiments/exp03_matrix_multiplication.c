#include <stdio.h>
#include <time.h>

#define MAX_DIMENSION 64
typedef long long MatrixValue;

static void multiply_standard(int n, const MatrixValue a[n][n],
                              const MatrixValue b[n][n],
                              MatrixValue result[n][n]) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < n; ++k)
                result[i][j] += a[i][k] * b[k][j];
        }
}

static void add_or_subtract(int n, const MatrixValue a[n][n],
                            const MatrixValue b[n][n],
                            MatrixValue result[n][n], int sign) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i][j] = a[i][j] + sign * b[i][j];
}

static void multiply_strassen(int n, const MatrixValue a[n][n],
                              const MatrixValue b[n][n],
                              MatrixValue result[n][n]) {
    if (n <= 2) {
        multiply_standard(n, a, b, result);
        return;
    }
    int half = n / 2;
    MatrixValue a11[half][half], a12[half][half];
    MatrixValue a21[half][half], a22[half][half];
    MatrixValue b11[half][half], b12[half][half];
    MatrixValue b21[half][half], b22[half][half];
    MatrixValue x[half][half], y[half][half];
    MatrixValue p1[half][half], p2[half][half], p3[half][half];
    MatrixValue p4[half][half], p5[half][half], p6[half][half], p7[half][half];
    MatrixValue c11[half][half], c12[half][half];
    MatrixValue c21[half][half], c22[half][half];
    for (int i = 0; i < half; ++i)
        for (int j = 0; j < half; ++j) {
            a11[i][j] = a[i][j]; a12[i][j] = a[i][j + half];
            a21[i][j] = a[i + half][j]; a22[i][j] = a[i + half][j + half];
            b11[i][j] = b[i][j]; b12[i][j] = b[i][j + half];
            b21[i][j] = b[i + half][j]; b22[i][j] = b[i + half][j + half];
        }
    add_or_subtract(half, a11, a22, x, 1);
    add_or_subtract(half, b11, b22, y, 1);
    multiply_strassen(half, x, y, p1);
    add_or_subtract(half, a21, a22, x, 1);
    multiply_strassen(half, x, b11, p2);
    add_or_subtract(half, b12, b22, y, -1);
    multiply_strassen(half, a11, y, p3);
    add_or_subtract(half, b21, b11, y, -1);
    multiply_strassen(half, a22, y, p4);
    add_or_subtract(half, a11, a12, x, 1);
    multiply_strassen(half, x, b22, p5);
    add_or_subtract(half, a21, a11, x, -1);
    add_or_subtract(half, b11, b12, y, 1);
    multiply_strassen(half, x, y, p6);
    add_or_subtract(half, a12, a22, x, -1);
    add_or_subtract(half, b21, b22, y, 1);
    multiply_strassen(half, x, y, p7);
    for (int i = 0; i < half; ++i)
        for (int j = 0; j < half; ++j) {
            c11[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
            c12[i][j] = p3[i][j] + p5[i][j];
            c21[i][j] = p2[i][j] + p4[i][j];
            c22[i][j] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
            result[i][j] = c11[i][j];
            result[i][j + half] = c12[i][j];
            result[i + half][j] = c21[i][j];
            result[i + half][j + half] = c22[i][j];
        }
}

int main(void) {
    int dimension, padded = 1;
    printf("Square matrix dimension (1-%d): ", MAX_DIMENSION);
    if (scanf("%d", &dimension) != 1 || dimension < 1 ||
        dimension > MAX_DIMENSION) return 1;
    while (padded < dimension) padded *= 2;
    MatrixValue a[padded][padded], b[padded][padded];
    MatrixValue standard[padded][padded], strassen[padded][padded];
    for (int i = 0; i < padded; ++i)
        for (int j = 0; j < padded; ++j) a[i][j] = b[i][j] = 0;
    printf("Enter A (%d x %d):\n", dimension, dimension);
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            if (scanf("%lld", &a[i][j]) != 1) return 1;
    puts("Enter B:");
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            if (scanf("%lld", &b[i][j]) != 1) return 1;
    clock_t start = clock();
    multiply_standard(padded, a, b, standard);
    clock_t middle = clock();
    multiply_strassen(padded, a, b, strassen);
    clock_t finish = clock();
    int matches = 1;
    for (int i = 0; i < padded; ++i)
        for (int j = 0; j < padded; ++j)
            if (standard[i][j] != strassen[i][j]) matches = 0;
    printf("Results match: %s\n", matches ? "yes" : "no");
    printf("Standard multiplication: %.3f ms\n",
           1000.0 * (middle - start) / CLOCKS_PER_SEC);
    printf("Strassen multiplication: %.3f ms\n",
           1000.0 * (finish - middle) / CLOCKS_PER_SEC);
    puts("Product:");
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) printf("%lld ", standard[i][j]);
        putchar('\n');
    }
    return matches ? 0 : 1;
}
