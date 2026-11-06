#include <limits.h>
#include <stdio.h>
#define MAXM 100
long long cost[MAXM+1][MAXM+1];int split[MAXM+1][MAXM+1];
void print_order(int i,int j){if(i==j){printf("A%d",i);return;}printf("(");print_order(i,split[i][j]);print_order(split[i][j]+1,j);printf(")");}
int main(void){int n;printf("Number of matrices (1-%d): ",MAXM);if(scanf("%d",&n)!=1||n<1||n>MAXM)return 1;long long p[n+1];printf("Enter %d dimensions: ",n+1);for(int i=0;i<=n;i++)if(scanf("%lld",&p[i])!=1||p[i]<=0)return 1;for(int len=2;len<=n;len++)for(int i=1;i+len-1<=n;i++){int j=i+len-1;cost[i][j]=LLONG_MAX;for(int k=i;k<j;k++){long long c=cost[i][k]+cost[k+1][j]+p[i-1]*p[k]*p[j];if(c<cost[i][j])cost[i][j]=c,split[i][j]=k;}}printf("Minimum scalar multiplications: %lld\nOptimal parenthesization: ",cost[1][n]);print_order(1,n);puts("");return 0;}
