#include <stdio.h>
#include <stdlib.h>

typedef struct { int weight, value; } Item;

static int compare_ratio(const void *left, const void *right) {
    const Item *a = left, *b = right;
    long long lhs = (long long)a->value * b->weight;
    long long rhs = (long long)b->value * a->weight;
    return (lhs < rhs) - (lhs > rhs);
}

static long long solve_backtracking(const Item items[], int count,
                                    int index, int capacity) {
    if (index == count) return 0;
    long long best = solve_backtracking(items, count, index + 1, capacity);
    if (items[index].weight <= capacity) {
        long long take = items[index].value +
            solve_backtracking(items, count, index + 1,
                               capacity - items[index].weight);
        if (take > best) best = take;
    }
    return best;
}

static long long upper_bound(const Item items[], int count, int index,
                             int capacity, long long value) {
    while (index < count && items[index].weight <= capacity) {
        capacity -= items[index].weight;
        value += items[index].value;
        ++index;
    }
    if (index < count)
        value += ((long long)items[index].value * capacity
                  + items[index].weight - 1) / items[index].weight;
    return value;
}

static long long solve_branch_and_bound(const Item items[], int count,
                                        int index, int capacity,
                                        long long value, long long best) {
    if (index == count) return value > best ? value : best;
    if (upper_bound(items, count, index, capacity, value) <= best) return best;
    best = solve_branch_and_bound(items, count, index + 1, capacity, value, best);
    if (items[index].weight <= capacity) {
        long long take = solve_branch_and_bound(items, count, index + 1,
            capacity - items[index].weight, value + items[index].value, best);
        if (take > best) best = take;
    }
    return best;
}

int main(void) {
    int count, capacity;
    printf("Number of items and capacity: ");
    if (scanf("%d%d", &count, &capacity) != 2 || count < 0 || capacity < 0) return 1;
    Item items[count > 0 ? count : 1], sorted[count > 0 ? count : 1];
    puts("Enter each item's positive weight and nonnegative value:");
    for (int i = 0; i < count; ++i) {
        if (scanf("%d%d", &items[i].weight, &items[i].value) != 2 ||
            items[i].weight <= 0 || items[i].value < 0) return 1;
        sorted[i] = items[i];
    }
    qsort(sorted, (size_t)count, sizeof sorted[0], compare_ratio);
    long long *dp = calloc((size_t)capacity + 1, sizeof *dp);
    if (dp == NULL) return 1;
    for (int i = 0; i < count; ++i)
        for (int c = capacity; c >= items[i].weight; --c)
            if (dp[c] < dp[c - items[i].weight] + items[i].value)
                dp[c] = dp[c - items[i].weight] + items[i].value;

    printf("Backtracking optimum: %lld\n",
           solve_backtracking(items, count, 0, capacity));
    printf("Branch-and-bound optimum: %lld\n",
           solve_branch_and_bound(sorted, count, 0, capacity, 0, 0));
    printf("Dynamic-programming optimum: %lld\n", dp[capacity]);
    free(dp);
    return 0;
}
