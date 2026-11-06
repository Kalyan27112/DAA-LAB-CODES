# DAA Lab Experiments 1-9

C implementations following the experiment list in the DAA course plan. Each experiment is a separate source file and can be compiled independently with a C99-or-later compiler.

## Build

```sh
gcc -std=c99 -O2 experiments/exp01_binary_search.c -o exp01
```

Run the executable and enter the requested data when prompted. Repeat the same build pattern for `experiments/exp02_merge_quick_sort.c` through `experiments/exp09_knapsack_comparison.c`, using a distinct output name for each executable.

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

Inputs are expected to be valid for each problem. Array sizes and matrix dimensions should be positive; Dijkstra requires nonnegative edge weights.
