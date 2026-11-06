#include <stdio.h>
#include <time.h>
#define MAXN 64
typedef long long ll;
void conventional(int n,const ll A[n][n],const ll B[n][n],ll C[n][n]){for(int i=0;i<n;i++)for(int j=0;j<n;j++){C[i][j]=0;for(int k=0;k<n;k++)C[i][j]+=A[i][k]*B[k][j];}}
void plus(int n,const ll A[n][n],const ll B[n][n],ll C[n][n],int sign){for(int i=0;i<n;i++)for(int j=0;j<n;j++)C[i][j]=A[i][j]+sign*B[i][j];}
void strassen(int n,const ll A[n][n],const ll B[n][n],ll C[n][n]){
 if(n<=2){conventional(n,A,B,C);return;}int h=n/2;
 ll a11[h][h],a12[h][h],a21[h][h],a22[h][h],b11[h][h],b12[h][h],b21[h][h],b22[h][h];
 ll x[h][h],y[h][h],p1[h][h],p2[h][h],p3[h][h],p4[h][h],p5[h][h],p6[h][h],p7[h][h];
 ll c11[h][h],c12[h][h],c21[h][h],c22[h][h];
 for(int i=0;i<h;i++)for(int j=0;j<h;j++){a11[i][j]=A[i][j];a12[i][j]=A[i][j+h];a21[i][j]=A[i+h][j];a22[i][j]=A[i+h][j+h];b11[i][j]=B[i][j];b12[i][j]=B[i][j+h];b21[i][j]=B[i+h][j];b22[i][j]=B[i+h][j+h];}
 plus(h,a11,a22,x,1);plus(h,b11,b22,y,1);strassen(h,x,y,p1);plus(h,a21,a22,x,1);strassen(h,x,b11,p2);plus(h,b12,b22,y,-1);strassen(h,a11,y,p3);plus(h,b21,b11,y,-1);strassen(h,a22,y,p4);plus(h,a11,a12,x,1);strassen(h,x,b22,p5);plus(h,a21,a11,x,-1);plus(h,b11,b12,y,1);strassen(h,x,y,p6);plus(h,a12,a22,x,-1);plus(h,b21,b22,y,1);strassen(h,x,y,p7);
 for(int i=0;i<h;i++)for(int j=0;j<h;j++){c11[i][j]=p1[i][j]+p4[i][j]-p5[i][j]+p7[i][j];c12[i][j]=p3[i][j]+p5[i][j];c21[i][j]=p2[i][j]+p4[i][j];c22[i][j]=p1[i][j]-p2[i][j]+p3[i][j]+p6[i][j];C[i][j]=c11[i][j];C[i][j+h]=c12[i][j];C[i+h][j]=c21[i][j];C[i+h][j+h]=c22[i][j];}
}
int main(void){int n,p=1;printf("Square matrix dimension (1-%d): ",MAXN);if(scanf("%d",&n)!=1||n<1||n>MAXN)return 1;while(p<n)p*=2;ll A[p][p],B[p][p],C[p][p],D[p][p];for(int i=0;i<p;i++)for(int j=0;j<p;j++)A[i][j]=B[i][j]=0;printf("Enter A (%dx%d):\n",n,n);for(int i=0;i<n;i++)for(int j=0;j<n;j++)scanf("%lld",&A[i][j]);puts("Enter B:");for(int i=0;i<n;i++)for(int j=0;j<n;j++)scanf("%lld",&B[i][j]);clock_t s=clock();conventional(p,A,B,C);clock_t m=clock();strassen(p,A,B,D);clock_t e=clock();int ok=1;for(int i=0;i<p;i++)for(int j=0;j<p;j++)if(C[i][j]!=D[i][j])ok=0;printf("Results match: %s\nConventional: %.3f ms\nStrassen: %.3f ms\nProduct:\n",ok?"yes":"no",1000.0*(m-s)/CLOCKS_PER_SEC,1000.0*(e-m)/CLOCKS_PER_SEC);for(int i=0;i<n;i++){for(int j=0;j<n;j++)printf("%lld ",C[i][j]);puts("");}return 0;}
