#include <stdio.h>
#include <stdlib.h>
typedef struct{int start,finish,id;}Activity;
int cmp(const void*a,const void*b){const Activity*x=a,*y=b;return (x->finish>y->finish)-(x->finish<y->finish);}
int main(void){int n;printf("Number of activities: ");if(scanf("%d",&n)!=1||n<0)return 1;Activity a[n?n:1];puts("Enter start and finish for each activity:");for(int i=0;i<n;i++){scanf("%d%d",&a[i].start,&a[i].finish);a[i].id=i+1;if(a[i].finish<a[i].start)return 1;}qsort(a,n,sizeof(Activity),cmp);int end=0,first=1,count=0;printf("Selected activity IDs: ");for(int i=0;i<n;i++)if(first||a[i].start>=end){printf("%d ",a[i].id);end=a[i].finish;first=0;count++;}printf("\nCount: %d\n",count);return 0;}
