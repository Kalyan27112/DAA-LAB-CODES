#include <stdio.h>

#define MAX_BOARD 15

static int queen_column[MAX_BOARD];
static int used_column[MAX_BOARD];
static int used_down_diagonal[2 * MAX_BOARD];
static int used_up_diagonal[2 * MAX_BOARD];
static int first_solution[MAX_BOARD];
static int board_size;
static unsigned long long solution_count;

static void place_queen(int row) {
    if (row == board_size) {
        if (solution_count == 0)
            for (int i = 0; i < board_size; ++i)
                first_solution[i] = queen_column[i];
        ++solution_count;
        return;
    }

    for (int column = 0; column < board_size; ++column) {
        int down = row - column + board_size - 1;
        int up = row + column;
        if (!used_column[column] && !used_down_diagonal[down] &&
            !used_up_diagonal[up]) {
            queen_column[row] = column;
            used_column[column] = 1;
            used_down_diagonal[down] = 1;
            used_up_diagonal[up] = 1;

            place_queen(row + 1);

            used_column[column] = 0;
            used_down_diagonal[down] = 0;
            used_up_diagonal[up] = 0;
        }
    }
}

int main(void) {
    printf("Board size (1-%d): ", MAX_BOARD);
    if (scanf("%d", &board_size) != 1 || board_size < 1 ||
        board_size > MAX_BOARD) return 1;

    place_queen(0);
    printf("Number of solutions: %llu\n", solution_count);
    if (solution_count > 0) {
        puts("One solution (Q marks a queen):");
        for (int row = 0; row < board_size; ++row) {
            for (int column = 0; column < board_size; ++column)
                printf("%c ", first_solution[row] == column ? 'Q' : '.');
            putchar('\n');
        }
    }
    return 0;
}
