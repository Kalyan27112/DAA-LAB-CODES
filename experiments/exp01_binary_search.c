#include <stdio.h>
#include <time.h>

int iterative(const int a[], int n, int x) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] < x) low = mid + 1; else high = mid - 1;
    }
    return -1;
}
int recursive(const int a[], int low, int high, int x) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (a[mid] == x) return mid;
    return a[mid] < x ? recursive(a, mid + 1, high, x) : recursive(a, low, mid - 1, x);
}
int main(void) {
    int n, x;
    printf("Number of sorted elements: "); if (scanf("%d", &n) != 1 || n <= 0) return 1;
    int a[n]; printf("Enter sorted elements: "); for (int i=0;i<n;i++) scanf("%d", &a[i]);
    printf("Target: "); scanf("%d", &x);
    clock_t s=clock(); int i=iterative(a,n,x); clock_t m=clock(); int j=recursive(a,0,n-1,x); clock_t e=clock();
    printf("Iterative index: %d (%.3f ms)\n",i,1000.0*(m-s)/CLOCKS_PER_SEC);
    printf("Recursive index: %d (%.3f ms)\n",j,1000.0*(e-m)/CLOCKS_PER_SEC);
    return 0;
}
