#include <stdio.h>
#define MAXN 20
int a[MAXN],pick[MAXN],n;long long target;int found=0;
void subset(int i,long long sum){if(sum==target){found=1;printf("{");int first=1;for(int k=0;k<n;k++)if(pick[k])printf("%s%d",first?"":",",a[k]),first=0;puts("}");return;}if(i==n||sum>target)return;pick[i]=1;subset(i+1,sum+a[i]);pick[i]=0;subset(i+1,sum);}
long long queen_count(int row,int n,int cols[],int d1[],int d2[]){if(row==n)return 1;long long count=0;for(int c=0;c<n;c++)if(!cols[c]&&!d1[row-c+n-1]&&!d2[row+c]){cols[c]=d1[row-c+n-1]=d2[row+c]=1;count+=queen_count(row+1,n,cols,d1,d2);cols[c]=d1[row-c+n-1]=d2[row+c]=0;}return count;}
int main(void){int q;printf("Subset sum: number of nonnegative values (max %d) and target: ",MAXN);if(scanf("%d%lld",&n,&target)!=2||n<0||n>MAXN||target<0)return 1;printf("Values: ");for(int i=0;i<n;i++){scanf("%d",&a[i]);if(a[i]<0)return 1;}subset(0,0);if(!found)puts("No subset found.");printf("N-Queens board size (1-%d): ",MAXN);if(scanf("%d",&q)!=1||q<1||q>MAXN)return 1;int cols[MAXN]={0},d1[2*MAXN]={0},d2[2*MAXN]={0};printf("Number of solutions: %lld\n",queen_count(0,q,cols,d1,d2));return 0;}
