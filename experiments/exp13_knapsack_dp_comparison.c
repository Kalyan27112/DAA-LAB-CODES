#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "knapsack_common.h"

#define MAX_ITEMS 30
#define MAX_CAPACITY 1000000

int main(void) {
    int count, capacity;
    printf("Number of items and capacity (max %d items): ", MAX_ITEMS);
    if (scanf("%d%d", &count, &capacity) != 2 || count < 0 ||
        count > MAX_ITEMS || capacity < 0 || capacity > MAX_CAPACITY) return 1;

    KnapsackItem items[MAX_ITEMS];
    puts("Enter each item's positive weight and nonnegative value:");
    for (int i = 0; i < count; ++i)
        if (scanf("%d%lld", &items[i].weight, &items[i].value) != 2 ||
            items[i].weight <= 0 || items[i].value < 0) return 1;

    clock_t start = clock();
    long long backtracking_value = knapsack_backtrack(items, count, 0, capacity);
    clock_t after_backtracking = clock();
    long long branch_value = knapsack_branch_and_bound(items, count, capacity);
    clock_t after_branch = clock();
    long long *dp = knapsack_dynamic_programming(items, count, capacity);
    clock_t after_dp = clock();
    if (branch_value < 0 || dp == NULL) {
        free(dp);
        return 1;
    }

    printf("Backtracking: value %lld, time %.3f ms\n", backtracking_value,
           1000.0 * (after_backtracking - start) / CLOCKS_PER_SEC);
    printf("Branch-and-bound: value %lld, time %.3f ms\n", branch_value,
           1000.0 * (after_branch - after_backtracking) / CLOCKS_PER_SEC);
    printf("Dynamic programming: value %lld, time %.3f ms\n", dp[capacity],
           1000.0 * (after_dp - after_branch) / CLOCKS_PER_SEC);

    int agree = backtracking_value == branch_value && branch_value == dp[capacity];
    free(dp);
    if (!agree) {
        fprintf(stderr, "The three methods returned different values.\n");
        return 2;
    }
    return 0;
}
