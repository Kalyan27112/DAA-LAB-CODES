#include <stdio.h>
#include <stdlib.h>

typedef struct { int start, finish, id; } Activity;

static int compare_finish(const void *left, const void *right) {
    const Activity *a = left, *b = right;
    if (a->finish < b->finish) return -1;
    if (a->finish > b->finish) return 1;
    return a->id - b->id;
}

int main(void) {
    int count;
    printf("Number of activities: ");
    if (scanf("%d", &count) != 1 || count < 0) return 1;
    Activity activities[count > 0 ? count : 1];
    puts("Enter each activity's start and finish time:");
    for (int i = 0; i < count; ++i) {
        if (scanf("%d%d", &activities[i].start, &activities[i].finish) != 2 ||
            activities[i].finish < activities[i].start) return 1;
        activities[i].id = i + 1;
    }
    qsort(activities, (size_t)count, sizeof activities[0], compare_finish);

    int selected = 0, last_finish = 0, have_last = 0;
    printf("Selected activity IDs: ");
    for (int i = 0; i < count; ++i) {
        if (!have_last || activities[i].start >= last_finish) {
            printf("%d ", activities[i].id);
            last_finish = activities[i].finish;
            have_last = 1;
            ++selected;
        }
    }
    printf("\nCount: %d\n", selected);
    return 0;
}
