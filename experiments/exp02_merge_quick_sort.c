#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void merge_sort(int a[],int l,int r){if(l>=r)return;int m=l+(r-l)/2;merge_sort(a,l,m);merge_sort(a,m+1,r);int n=r-l+1,t[n],i=l,j=m+1,k=0;while(i<=m&&j<=r)t[k++]=a[i]<=a[j]?a[i++]:a[j++];while(i<=m)t[k++]=a[i++];while(j<=r)t[k++]=a[j++];for(i=0;i<n;i++)a[l+i]=t[i];}
int partition(int a[],int l,int r){int p=a[r],i=l;for(int j=l;j<r;j++)if(a[j]<=p){int t=a[i];a[i++]=a[j];a[j]=t;}int t=a[i];a[i]=a[r];a[r]=t;return i;}
void quick_sort(int a[],int l,int r){if(l<r){int p=partition(a,l,r);quick_sort(a,l,p-1);quick_sort(a,p+1,r);}}
void show(const char*name,const int a[],int n,double ms){printf("%s (%.3f ms): ",name,ms);for(int i=0;i<n;i++)printf("%d ",a[i]);puts("");}
int main(void){int n;printf("Number of elements: ");if(scanf("%d",&n)!=1||n<=0)return 1;int a[n],b[n];printf("Enter elements: ");for(int i=0;i<n;i++)scanf("%d",&a[i]),b[i]=a[i];clock_t s=clock();merge_sort(a,0,n-1);clock_t m=clock();quick_sort(b,0,n-1);clock_t e=clock();show("Merge sort",a,n,1000.0*(m-s)/CLOCKS_PER_SEC);show("Quick sort",b,n,1000.0*(e-m)/CLOCKS_PER_SEC);return 0;}
