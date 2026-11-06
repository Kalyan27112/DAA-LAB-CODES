#include <stdio.h>
#include <stdlib.h>
typedef struct{int w,v,id;}Item;
int cmp(const void*a,const void*b){const Item*x=a,*y=b;long long l=(long long)x->v*y->w,r=(long long)y->v*x->w;return (l<r)-(l>r);}
int main(void){int n,W;printf("Items and capacity: ");if(scanf("%d%d",&n,&W)!=2||n<0||W<0)return 1;Item a[n?n:1],g[n?n:1];puts("Enter positive weight and nonnegative value per item:");for(int i=0;i<n;i++){scanf("%d%d",&a[i].w,&a[i].v);if(a[i].w<=0||a[i].v<0)return 1;a[i].id=i+1;g[i]=a[i];}qsort(g,n,sizeof(Item),cmp);int rem=W;long long gv=0;printf("Greedy items: ");for(int i=0;i<n;i++)if(g[i].w<=rem){rem-=g[i].w;gv+=g[i].v;printf("%d ",g[i].id);}long long dp[W+1];for(int c=0;c<=W;c++)dp[c]=0;for(int i=0;i<n;i++)for(int c=W;c>=a[i].w;c--)if(dp[c]<dp[c-a[i].w]+a[i].v)dp[c]=dp[c-a[i].w]+a[i].v;printf("\nGreedy value (heuristic): %lld\nOptimal 0/1 DP value: %lld\n",gv,dp[W]);return 0;}
