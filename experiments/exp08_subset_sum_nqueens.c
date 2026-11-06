#include <stdio.h>

#define MAX_VALUES 20
#define MAX_BOARD 20

static int values[MAX_VALUES], chosen[MAX_VALUES], value_count;
static long long target;
static int solution_found;

static void print_subset(void) {
    int first = 1;
    putchar('{');
    for (int i = 0; i < value_count; ++i) {
        if (chosen[i]) {
            printf("%s%d", first ? "" : ", ", values[i]);
            first = 0;
        }
    }
    puts("}");
}

static void find_subsets(int index, long long sum) {
    if (sum > target) return;
    if (index == value_count) {
        if (sum == target) {
            solution_found = 1;
            print_subset();
        }
        return;
    }
    chosen[index] = 1;
    find_subsets(index + 1, sum + values[index]);
    chosen[index] = 0;
    find_subsets(index + 1, sum);
}

static long long count_queen_solutions(int row, int size, int columns[],
                                       int diagonals_down[], int diagonals_up[]) {
    if (row == size) return 1;
    long long total = 0;
    for (int column = 0; column < size; ++column) {
        int down = row - column + size - 1;
        int up = row + column;
        if (!columns[column] && !diagonals_down[down] && !diagonals_up[up]) {
            columns[column] = diagonals_down[down] = diagonals_up[up] = 1;
            total += count_queen_solutions(row + 1, size, columns,
                                           diagonals_down, diagonals_up);
            columns[column] = diagonals_down[down] = diagonals_up[up] = 0;
        }
    }
    return total;
}

int main(void) {
    printf("Subset sum: number of nonnegative values (max %d) and target: ", MAX_VALUES);
    if (scanf("%d%lld", &value_count, &target) != 2 || value_count < 0 ||
        value_count > MAX_VALUES || target < 0) return 1;
    printf("Values: ");
    for (int i = 0; i < value_count; ++i)
        if (scanf("%d", &values[i]) != 1 || values[i] < 0) return 1;
    find_subsets(0, 0);
    if (!solution_found) puts("No subset found.");

    int size;
    printf("N-Queens board size (1-%d): ", MAX_BOARD);
    if (scanf("%d", &size) != 1 || size < 1 || size > MAX_BOARD) return 1;
    int columns[MAX_BOARD] = {0};
    int diagonals_down[2 * MAX_BOARD] = {0};
    int diagonals_up[2 * MAX_BOARD] = {0};
    printf("Number of solutions: %lld\n",
           count_queen_solutions(0, size, columns, diagonals_down, diagonals_up));
    return 0;
}
