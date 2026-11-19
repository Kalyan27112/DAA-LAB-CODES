#include <stdio.h>
#include <time.h>
#include "knapsack_common.h"

#define MAX_ITEMS 30

int main(void) {
    int count, capacity;
    printf("Number of items and capacity (max %d items): ", MAX_ITEMS);
    if (scanf("%d%d", &count, &capacity) != 2 || count < 0 ||
        count > MAX_ITEMS || capacity < 0) return 1;

    KnapsackItem items[MAX_ITEMS];
    puts("Enter each item's positive weight and nonnegative value:");
    for (int i = 0; i < count; ++i)
        if (scanf("%d%lld", &items[i].weight, &items[i].value) != 2 ||
            items[i].weight <= 0 || items[i].value < 0) return 1;

    clock_t start = clock();
    long long backtracking_value = knapsack_backtrack(items, count, 0, capacity);
    clock_t middle = clock();
    long long branch_value = knapsack_branch_and_bound(items, count, capacity);
    clock_t finish = clock();
    if (branch_value < 0) return 1;

    printf("Backtracking best value: %lld (%.3f ms)\n", backtracking_value,
           1000.0 * (middle - start) / CLOCKS_PER_SEC);
    printf("Branch-and-bound best value: %lld (%.3f ms)\n", branch_value,
           1000.0 * (finish - middle) / CLOCKS_PER_SEC);
    return backtracking_value == branch_value ? 0 : 2;
}
