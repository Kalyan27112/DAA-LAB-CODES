#include <stdio.h>
#include <string.h>
#include "string_matching_common.h"

#define MAX_TEXT_LENGTH 100000

static int read_line(const char *prompt, char buffer[], size_t capacity) {
    printf("%s", prompt);
    if (fgets(buffer, (int)capacity, stdin) == NULL) return 0;
    buffer[strcspn(buffer, "\n")] = '\0';
    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\r') buffer[length - 1] = '\0';
    return 1;
}

static void print_matches(const char *name, int count, const size_t positions[]) {
    printf("%s positions (0-based): ", name);
    if (count == 0) printf("none");
    for (int i = 0; i < count; ++i) printf("%s%zu", i ? ", " : "", positions[i]);
    putchar('\n');
}

int main(void) {
    char text[MAX_TEXT_LENGTH + 2];
    char pattern[MAX_TEXT_LENGTH + 2];
    if (!read_line("Text: ", text, sizeof text) ||
        !read_line("Pattern: ", pattern, sizeof pattern)) return 1;

    size_t n = strlen(text), m = strlen(pattern);
    size_t *naive = malloc((n + 1) * sizeof *naive);
    size_t *rabin = malloc((n + 1) * sizeof *rabin);
    size_t *kmp = malloc((n + 1) * sizeof *kmp);
    if (naive == NULL || rabin == NULL || kmp == NULL) {
        free(naive); free(rabin); free(kmp);
        return 1;
    }

    int naive_count = match_naive(text, n, pattern, m, naive);
    int rabin_count = match_rabin_karp(text, n, pattern, m, rabin);
    int kmp_count = match_kmp(text, n, pattern, m, kmp);
    if (kmp_count < 0) {
        free(naive); free(rabin); free(kmp);
        return 1;
    }

    print_matches("Naive", naive_count, naive);
    print_matches("Rabin-Karp", rabin_count, rabin);
    print_matches("KMP", kmp_count, kmp);
    int agree = naive_count == rabin_count && naive_count == kmp_count;
    for (int i = 0; agree && i < naive_count; ++i)
        agree = naive[i] == rabin[i] && naive[i] == kmp[i];
    printf("All methods agree: %s\n", agree ? "yes" : "no");

    free(naive); free(rabin); free(kmp);
    return agree ? 0 : 2;
}
