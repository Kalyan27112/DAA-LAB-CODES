#include <stdio.h>
#include <string.h>
#include <time.h>
#include "string_matching_common.h"

#define MAX_TEXT_LENGTH 100000
#define MAX_BENCHMARK_WORK 1000000ULL
#define MAX_REPEATS 1000

static int read_line(const char *prompt, char buffer[], size_t capacity) {
    printf("%s", prompt);
    if (fgets(buffer, (int)capacity, stdin) == NULL) return 0;
    buffer[strcspn(buffer, "\n")] = '\0';
    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\r') buffer[length - 1] = '\0';
    return 1;
}

int main(void) {
    char text[MAX_TEXT_LENGTH + 2];
    char pattern[MAX_TEXT_LENGTH + 2];
    if (!read_line("Text: ", text, sizeof text) ||
        !read_line("Pattern: ", pattern, sizeof pattern)) return 1;

    size_t n = strlen(text), m = strlen(pattern);
    size_t *positions = malloc((n + 1) * sizeof *positions);
    if (positions == NULL) return 1;

    unsigned long long work = (unsigned long long)(n + 1) * (m ? m : 1);
    int repeats = work >= MAX_BENCHMARK_WORK ? 1 :
                  (int)(MAX_BENCHMARK_WORK / work);
    if (repeats > MAX_REPEATS) repeats = MAX_REPEATS;

    volatile int checksum = 0;
    clock_t start = clock();
    int naive_count = 0;
    for (int r = 0; r < repeats; ++r)
        naive_count = match_naive(text, n, pattern, m, positions), checksum += naive_count;
    clock_t naive_end = clock();

    int rabin_count = 0;
    for (int r = 0; r < repeats; ++r)
        rabin_count = match_rabin_karp(text, n, pattern, m, positions), checksum += rabin_count;
    clock_t rabin_end = clock();

    int kmp_count = 0;
    for (int r = 0; r < repeats; ++r) {
        kmp_count = match_kmp(text, n, pattern, m, positions);
        if (kmp_count < 0) { free(positions); return 1; }
        checksum += kmp_count;
    }
    clock_t kmp_end = clock();

    printf("Matching positions found: naive=%d, Rabin-Karp=%d, KMP=%d\n",
           naive_count, rabin_count, kmp_count);
    printf("Repetitions per method: %d\n", repeats);
    printf("Naive total time: %.3f ms\n",
           1000.0 * (naive_end - start) / CLOCKS_PER_SEC);
    printf("Rabin-Karp total time: %.3f ms\n",
           1000.0 * (rabin_end - naive_end) / CLOCKS_PER_SEC);
    printf("KMP total time: %.3f ms\n",
           1000.0 * (kmp_end - rabin_end) / CLOCKS_PER_SEC);
    (void)checksum;
    free(positions);
    return naive_count == rabin_count && naive_count == kmp_count ? 0 : 2;
}
