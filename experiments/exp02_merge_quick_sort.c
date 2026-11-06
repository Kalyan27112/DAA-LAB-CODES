#include <stdio.h>
#include <time.h>

static void merge_sort(int values[], int low, int high) {
    if (low >= high) return;
    int middle = low + (high - low) / 2;
    merge_sort(values, low, middle);
    merge_sort(values, middle + 1, high);
    int length = high - low + 1;
    int temporary[length];
    int left = low, right = middle + 1, out = 0;
    while (left <= middle && right <= high) {
        if (values[left] <= values[right]) temporary[out++] = values[left++];
        else temporary[out++] = values[right++];
    }
    while (left <= middle) temporary[out++] = values[left++];
    while (right <= high) temporary[out++] = values[right++];
    for (int i = 0; i < length; ++i) values[low + i] = temporary[i];
}

static int partition(int values[], int low, int high) {
    int pivot = values[high], boundary = low;
    for (int i = low; i < high; ++i) {
        if (values[i] <= pivot) {
            int temporary = values[boundary];
            values[boundary++] = values[i];
            values[i] = temporary;
        }
    }
    int temporary = values[boundary];
    values[boundary] = values[high];
    values[high] = temporary;
    return boundary;
}

static void quick_sort(int values[], int low, int high) {
    if (low >= high) return;
    int pivot = partition(values, low, high);
    quick_sort(values, low, pivot - 1);
    quick_sort(values, pivot + 1, high);
}

static void print_result(const char *label, const int values[], int count,
                         double milliseconds) {
    printf("%s (%.3f ms): ", label, milliseconds);
    for (int i = 0; i < count; ++i) printf("%d ", values[i]);
    putchar('\n');
}

int main(void) {
    int count;
    printf("Number of elements: ");
    if (scanf("%d", &count) != 1 || count <= 0) return 1;
    int merge_values[count], quick_values[count];
    printf("Enter elements: ");
    for (int i = 0; i < count; ++i) {
        if (scanf("%d", &merge_values[i]) != 1) return 1;
        quick_values[i] = merge_values[i];
    }
    clock_t start = clock();
    merge_sort(merge_values, 0, count - 1);
    clock_t middle = clock();
    quick_sort(quick_values, 0, count - 1);
    clock_t finish = clock();
    print_result("Merge sort", merge_values, count,
                 1000.0 * (middle - start) / CLOCKS_PER_SEC);
    print_result("Quick sort", quick_values, count,
                 1000.0 * (finish - middle) / CLOCKS_PER_SEC);
    return 0;
}
