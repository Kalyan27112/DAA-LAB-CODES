#include <stdio.h>
#include <stdlib.h>

typedef struct { int weight, value, id; } Item;

static int compare_ratio(const void *left, const void *right) {
    const Item *a = left, *b = right;
    long long lhs = (long long)a->value * b->weight;
    long long rhs = (long long)b->value * a->weight;
    return (lhs < rhs) - (lhs > rhs);
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
        items[i].id = i + 1;
        sorted[i] = items[i];
    }
    qsort(sorted, (size_t)count, sizeof sorted[0], compare_ratio);
    int remaining = capacity;
    long long greedy_value = 0;
    printf("Greedy selected item IDs: ");
    for (int i = 0; i < count; ++i) {
        if (sorted[i].weight <= remaining) {
            remaining -= sorted[i].weight;
            greedy_value += sorted[i].value;
            printf("%d ", sorted[i].id);
        }
    }

    long long *dp = calloc((size_t)capacity + 1, sizeof *dp);
    if (dp == NULL) return 1;
    for (int i = 0; i < count; ++i)
        for (int c = capacity; c >= items[i].weight; --c)
            if (dp[c] < dp[c - items[i].weight] + items[i].value)
                dp[c] = dp[c - items[i].weight] + items[i].value;
    printf("\nGreedy value (heuristic): %lld\n", greedy_value);
    printf("Optimal 0/1 dynamic-programming value: %lld\n", dp[capacity]);
    free(dp);
    return 0;
}
