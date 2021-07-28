#include<stdio.h>
#include<time.h>
#include<math.h>
clock_t start,stop;
double duration;
#define MAXN    10
#define MAXK    1e7
double f1(int n,double a[],double x);
double f2(int n,double a[],double x);

int main(){
    int i;
    double a[MAXN];
    for (i=0;i<MAXN;i++)a[i] = (double)i;

    start = clock();
    for(i=0;i<MAXK;i++)
        f1(MAXN,a,1.1);
    stop = clock();
    duration = (double)(stop-start)/CLOCKS_PER_SEC/MAXK;
    printf("ticks1 = %f\n",(double)(stop-start));
    printf("duration1 = %6.2e\n",duration);


    start = clock();
    for(i=0;i<MAXK;i++)
        f2(MAXN,a,1.1);
    stop = clock();
    duration = (double)(stop-start)/CLOCKS_PER_SEC/MAXK;
    printf("ticks2 = %f\n",(double)(stop-start));
    printf("duration2 = %6.2e\n",duration);

    return 0;
}
double f1(int n,double a[],double x){
    int i;
    double p = a[0];
    for (i=1;i<=n;i++)
        p+= (a[i] * pow(x,i));
    return p;
}
double f2(int n,double a[],double x){
    int i;
    double p = a[n];
    for (i = n;i>0;i--)
        p = a[i-1] + x*p;
    return p;
}