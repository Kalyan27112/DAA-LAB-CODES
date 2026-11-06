#include <stdio.h>
#include <time.h>

static int iterative_search(const int values[], int count, int target) {
    int low = 0;
    int high = count - 1;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (values[middle] == target) return middle;
        if (values[middle] < target) low = middle + 1;
        else high = middle - 1;
    }
    return -1;
}

static int recursive_search(const int values[], int low, int high, int target) {
    if (low > high) return -1;
    int middle = low + (high - low) / 2;
    if (values[middle] == target) return middle;
    if (values[middle] < target)
        return recursive_search(values, middle + 1, high, target);
    return recursive_search(values, low, middle - 1, target);
}

int main(void) {
    int count, target;
    printf("Number of sorted elements: ");
    if (scanf("%d", &count) != 1 || count <= 0) return 1;
    int values[count];
    printf("Enter sorted elements: ");
    for (int i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) return 1;
        if (i > 0 && values[i] < values[i - 1]) {
            fprintf(stderr, "Input must be sorted.\n");
            return 1;
        }
    }
    printf("Target: ");
    if (scanf("%d", &target) != 1) return 1;
    clock_t start = clock();
    int iterative_result = iterative_search(values, count, target);
    clock_t middle = clock();
    int recursive_result = recursive_search(values, 0, count - 1, target);
    clock_t finish = clock();
    printf("Iterative index: %d (%.3f ms)\n", iterative_result,
           1000.0 * (middle - start) / CLOCKS_PER_SEC);
    printf("Recursive index: %d (%.3f ms)\n", recursive_result,
           1000.0 * (finish - middle) / CLOCKS_PER_SEC);
    return 0;
}
