#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void print(int *a, int n);

void swap(int *x, int *y) {
    if( *x == *y) return;
    
    int tem = *x;
        *x = *y;
        *y = tem;
}

void sort(int *a, int l, int r) {
    if(l >= r) return;

    int s = l-1, e = r, ss = l-1, ee = r;
    int p = a[r];
    
    while(1) {

        while(a[++s] < p);
        while(a[--e] > p) if(e == l) break;

        if( e <= s) break;

        swap(&a[s], &a[e]);

        if(a[s] == p) swap(&a[++ss], &a[s]);
        if(a[e] == p) swap(&a[--ee], &a[e]);
    }
    
    swap(&a[s], &a[r]);
    int x = s + 1;
    s = s - 1;
    for(int i = l; i <= ss; i++) {
        swap(&a[i], &a[s--]);
    }

    for(int i = r - 1; i >= ee; i--) {
        swap(&a[i], &a[x++]);
    }
    
    sort(a,l,s);
    sort(a,x,r);
}

void print(int *a, int n) {

    for(int i = 0; i <= n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void gen(int *a, int n) {

    for(int i = 0; i < n; i++) {
        a[i] = rand() % 10;
    }
}

int main() {
    srand(time(NULL));

    int n = 100000000;
    int *a = (int*)malloc(sizeof(int) * n);
    
    gen(a,n );
    // print(a,n - 1 );
    sort(a,0,n - 1);
    print(a,n - 1);

    free(a);
}