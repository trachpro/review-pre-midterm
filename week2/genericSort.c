#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void my_memcpy(void *des, void *sour, size_t size) {

    char *x = (char *)des;
    char *y = (char *)sour;

    for(int i = 0; i< size; i++) {
        x[i] = y[i];
    }
}

void swap(void *x, void *y, size_t size) {

    char *tem = (char*)malloc(sizeof(char) * size);

    my_memcpy(tem,x,size);
    my_memcpy(x,y, size);
    my_memcpy(y,tem, size);
}

int compare(void const *x, void const *y) {

    return *(int*)x - *(int*)y;
}

void sort(void *a, int l, int r, size_t size, int cmp(const void *x, const void *y)) {

    if(l >= r) return; 

    int s = l - 1, ss = l -1;
    int e = r, ee = r;

    char *p = (char*)a +size * r;

    while(1) {

        while(cmp(p, a + size * (++s)) > 0);
        while(cmp(p, a + size * (--e)) < 0) if(e == l) break;

        if(e <= s) break;

        swap(a + size*s, a + size*e, size);

        if(cmp(p, a + size * s) == 0) swap(a + size*s, a + size*(++ss), size);
        if(cmp(p, a + size * e) == 0) swap(a + size*e, a + size*(--ee), size);
    }

    swap(a + size *s, a + size *r, size);

    e = s +1;
    s = s - 1;

    for(int i = l; i<= ss; i++) swap(a + size*i, a + size*(s--), size);
    for(int i = r - 1; i >= ee; i--) swap(a + size*i, a+ size*(e++), size);

    sort(a, l, s, size, cmp);
    sort(a, e, r, size, cmp);
}

void print(int *a, int n) {
    
        for(int i = 0; i <= n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

int search(void *a, int l, int r,int size,void *key, int cmp(void const *x, void const *y)) {

    if(l > r) return -1;

    int mid = (l + r)/2;
    if(compare(a +mid * size, key) == 0) return mid;

    else if(compare(a +mid*size, key) > 0) return search(a,l, mid-1, size, key, cmp);

    else return search(a,mid + 1, r,size , key, cmp);
}


int main() {

    int n;
    int a[] = {9,7,6,2,8,6,5,6,3,2,4,6,6,4,8,9};
    int key = 7;
    sort(a,0,15,sizeof(int), compare);
    print(a,15);
    printf("%d\n", search(a,0,15, sizeof(int),&key,compare));
}