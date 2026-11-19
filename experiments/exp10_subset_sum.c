#include <stdio.h>

#define MAX_VALUES 30

static int values[MAX_VALUES];
static int selected[MAX_VALUES];
static int count;
static long long target;
static unsigned long long solutions;

static void print_current_subset(void) {
    int first = 1;
    putchar('{');
    for (int i = 0; i < count; ++i) {
        if (selected[i]) {
            printf("%s%d", first ? "" : ", ", values[i]);
            first = 0;
        }
    }
    puts("}");
}

static void search_subsets(int index, long long sum) {
    if (sum > target) return;
    if (index == count) {
        if (sum == target) {
            ++solutions;
            print_current_subset();
        }
        return;
    }

    selected[index] = 1;
    search_subsets(index + 1, sum + values[index]);
    selected[index] = 0;
    search_subsets(index + 1, sum);
}

int main(void) {
    printf("Number of nonnegative values (max %d) and target: ", MAX_VALUES);
    if (scanf("%d%lld", &count, &target) != 2 || count < 0 ||
        count > MAX_VALUES || target < 0) return 1;

    printf("Enter the values: ");
    for (int i = 0; i < count; ++i)
        if (scanf("%d", &values[i]) != 1 || values[i] < 0) return 1;

    search_subsets(0, 0);
    if (solutions == 0) puts("No subset has the required sum.");
    printf("Number of matching subsets: %llu\n", solutions);
    return 0;
}
