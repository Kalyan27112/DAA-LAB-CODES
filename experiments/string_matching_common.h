#ifndef STRING_MATCHING_COMMON_H
#define STRING_MATCHING_COMMON_H

#include <stdlib.h>
#include <string.h>

static int match_naive(const char *text, size_t text_length,
                       const char *pattern, size_t pattern_length,
                       size_t positions[]) {
    int matches = 0;
    if (pattern_length == 0) {
        for (size_t i = 0; i <= text_length; ++i) positions[matches++] = i;
        return matches;
    }
    if (pattern_length > text_length) return 0;
    for (size_t start = 0; start <= text_length - pattern_length; ++start)
        if (memcmp(text + start, pattern, pattern_length) == 0)
            positions[matches++] = start;
    return matches;
}

static int match_rabin_karp(const char *text, size_t text_length,
                            const char *pattern, size_t pattern_length,
                            size_t positions[]) {
    const long long base = 256;
    const long long modulus = 1000000007;
    int matches = 0;
    if (pattern_length == 0) {
        for (size_t i = 0; i <= text_length; ++i) positions[matches++] = i;
        return matches;
    }
    if (pattern_length > text_length) return 0;

    long long high_order = 1, pattern_hash = 0, window_hash = 0;
    for (size_t i = 1; i < pattern_length; ++i)
        high_order = (high_order * base) % modulus;
    for (size_t i = 0; i < pattern_length; ++i) {
        pattern_hash = (base * pattern_hash + (unsigned char)pattern[i]) % modulus;
        window_hash = (base * window_hash + (unsigned char)text[i]) % modulus;
    }

    for (size_t start = 0; start <= text_length - pattern_length; ++start) {
        if (pattern_hash == window_hash &&
            memcmp(text + start, pattern, pattern_length) == 0)
            positions[matches++] = start;
        if (start < text_length - pattern_length) {
            long long leading = (unsigned char)text[start];
            window_hash = (base * (window_hash - leading * high_order) +
                           (unsigned char)text[start + pattern_length]) % modulus;
            if (window_hash < 0) window_hash += modulus;
        }
    }
    return matches;
}

static int match_kmp(const char *text, size_t text_length,
                     const char *pattern, size_t pattern_length,
                     size_t positions[]) {
    int matches = 0;
    if (pattern_length == 0) {
        for (size_t i = 0; i <= text_length; ++i) positions[matches++] = i;
        return matches;
    }
    if (pattern_length > text_length) return 0;

    size_t *prefix = malloc(pattern_length * sizeof *prefix);
    if (prefix == NULL) return -1;
    prefix[0] = 0;
    for (size_t i = 1, length = 0; i < pattern_length;) {
        if (pattern[i] == pattern[length]) prefix[i++] = ++length;
        else if (length != 0) length = prefix[length - 1];
        else prefix[i++] = 0;
    }

    for (size_t i = 0, j = 0; i < text_length;) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;
            if (j == pattern_length) {
                positions[matches++] = i - j;
                j = prefix[j - 1];
            }
        } else if (j != 0) {
            j = prefix[j - 1];
        } else {
            ++i;
        }
    }
    free(prefix);
    return matches;
}

#endif
