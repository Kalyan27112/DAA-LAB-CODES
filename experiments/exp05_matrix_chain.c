#include <limits.h>
#include <stdio.h>

#define MAX_MATRICES 100
static long long cost[MAX_MATRICES + 1][MAX_MATRICES + 1];
static int split[MAX_MATRICES + 1][MAX_MATRICES + 1];

static void print_order(int first, int last) {
    if (first == last) {
        printf("A%d", first);
        return;
    }
    putchar('(');
    print_order(first, split[first][last]);
    print_order(split[first][last] + 1, last);
    putchar(')');
}

int main(void) {
    int count;
    printf("Number of matrices (1-%d): ", MAX_MATRICES);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_MATRICES) return 1;
    long long dimensions[count + 1];
    printf("Enter %d positive dimensions: ", count + 1);
    for (int i = 0; i <= count; ++i)
        if (scanf("%lld", &dimensions[i]) != 1 || dimensions[i] <= 0) return 1;

    for (int length = 2; length <= count; ++length) {
        for (int first = 1; first + length - 1 <= count; ++first) {
            int last = first + length - 1;
            cost[first][last] = LLONG_MAX;
            for (int k = first; k < last; ++k) {
                long long candidate = cost[first][k] + cost[k + 1][last]
                    + dimensions[first - 1] * dimensions[k] * dimensions[last];
                if (candidate < cost[first][last]) {
                    cost[first][last] = candidate;
                    split[first][last] = k;
                }
            }
        }
    }
    printf("Minimum scalar multiplications: %lld\n", cost[1][count]);
    printf("Optimal parenthesization: ");
    print_order(1, count);
    putchar('\n');
    return 0;
}
