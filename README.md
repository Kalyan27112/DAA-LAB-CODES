# DAA Lab Experiments 1-15

C implementations following the experiment list in the DAA course plan. Each experiment is a separate source file and can be compiled independently with a C99-or-later compiler.

## Build

```sh
gcc -std=c99 -O2 experiments/exp01_binary_search.c -o exp01
```

Run the executable and enter the requested data when prompted. Each experiment is a separate C program. Experiments 12 and 13 include `knapsack_common.h`; Experiments 14 and 15 include `string_matching_common.h`. Keep the relevant header in the same folder when compiling.

## Experiments

1. Iterative and recursive binary search, with elapsed-time comparison.
2. Merge sort and quick sort on the same input, with elapsed-time comparison.
3. Conventional and Strassen matrix multiplication, with result check and timing.
4. Greedy activity selection.
5. Dynamic-programming matrix-chain multiplication with optimal parenthesization.
6. Dijkstra and Bellman-Ford single-source shortest paths (nonnegative weights for Dijkstra; negative edges allowed for Bellman-Ford; negative cycles reported).
7. Greedy-by-value-density heuristic and exact dynamic programming for 0/1 knapsack.
8. Backtracking subset sum and N-Queens.
9. 0/1 knapsack comparison using backtracking, branch-and-bound, and dynamic programming.
10. Subset sum using include-or-exclude backtracking.
11. N-Queens using row-by-row backtracking.
12. 0/1 knapsack comparison using backtracking and branch-and-bound.
13. 0/1 knapsack comparison using backtracking, branch-and-bound, and dynamic programming.
14. Naive, Rabin-Karp, and Knuth-Morris-Pratt matching positions.
15. Runtime comparison of naive, Rabin-Karp, and Knuth-Morris-Pratt matching.

Inputs are expected to be valid for each problem. Array sizes and matrix dimensions should be positive; Dijkstra requires nonnegative edge weights.
