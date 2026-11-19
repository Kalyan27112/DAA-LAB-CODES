#ifndef KNAPSACK_COMMON_H
#define KNAPSACK_COMMON_H

#include <stddef.h>
#include <stdlib.h>

typedef struct {
    int weight;
    long long value;
} KnapsackItem;

typedef struct {
    const KnapsackItem *items;
    int count;
    long long best;
} BranchContext;

static int knapsack_density_order(const void *left, const void *right) {
    const KnapsackItem *a = left;
    const KnapsackItem *b = right;
    long double ratio_a = (long double)a->value / a->weight;
    long double ratio_b = (long double)b->value / b->weight;
    if (ratio_a > ratio_b) return -1;
    if (ratio_a < ratio_b) return 1;
    return 0;
}

static long long knapsack_backtrack(const KnapsackItem items[], int count,
                                    int index, int remaining) {
    if (index == count) return 0;
    long long best = knapsack_backtrack(items, count, index + 1, remaining);
    if (items[index].weight <= remaining) {
        long long take = items[index].value + knapsack_backtrack(
            items, count, index + 1, remaining - items[index].weight);
        if (take > best) best = take;
    }
    return best;
}

static long double knapsack_upper_bound(const KnapsackItem items[], int count,
                                        int index, int remaining,
                                        long long value) {
    long double bound = value;
    while (index < count && items[index].weight <= remaining) {
        remaining -= items[index].weight;
        bound += items[index].value;
        ++index;
    }
    if (index < count) {
        long double fraction = (long double)items[index].value * remaining /
                               items[index].weight;
        /* Round upward so floating-point error cannot prune an optimal branch. */
        bound += (long long)fraction + 1;
    }
    return bound;
}

static void knapsack_branch_search(BranchContext *context, int index,
                                   int remaining, long long value) {
    if (index == context->count) {
        if (value > context->best) context->best = value;
        return;
    }
    if (knapsack_upper_bound(context->items, context->count, index,
                             remaining, value) <= context->best) return;

    knapsack_branch_search(context, index + 1, remaining, value);
    if (context->items[index].weight <= remaining)
        knapsack_branch_search(context, index + 1,
            remaining - context->items[index].weight,
            value + context->items[index].value);
}

static long long knapsack_branch_and_bound(const KnapsackItem items[],
                                           int count, int capacity) {
    KnapsackItem *ordered = malloc((size_t)(count > 0 ? count : 1) *
                                   sizeof *ordered);
    if (ordered == NULL) return -1;
    for (int i = 0; i < count; ++i) ordered[i] = items[i];
    qsort(ordered, (size_t)count, sizeof *ordered, knapsack_density_order);

    BranchContext context = {ordered, count, 0};
    knapsack_branch_search(&context, 0, capacity, 0);
    free(ordered);
    return context.best;
}

static long long *knapsack_dynamic_programming(const KnapsackItem items[],
                                                int count, int capacity) {
    long long *dp = calloc((size_t)capacity + 1, sizeof *dp);
    if (dp == NULL) return NULL;
    for (int i = 0; i < count; ++i)
        for (int c = capacity; c >= items[i].weight; --c) {
            long long candidate = dp[c - items[i].weight] + items[i].value;
            if (candidate > dp[c]) dp[c] = candidate;
        }
    return dp;
}

#endif
