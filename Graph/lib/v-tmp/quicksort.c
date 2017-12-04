#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 10000000

int *b;
int *a;

void swap (int *a,int *b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void copyArr(int b[], int a[]) {
  for (int i; i < ARR_SIZE; ++i) {
    a[i] = b[i];
  }
}

void randomArr(int *b, int size) {
  for (int i = 0; i < size; ++i) {
    b[i] = rand();
  }
}



int partition2p(int *a, int l, int r);

void quicksort2p(int *a, int l, int r) {
  
    if (l < r) {
      int pi = partition2p(a, l, r);

        quicksort2p(a, l, pi - 1);  // Before pi
        quicksort2p(a, pi + 1, r); // After pi
    }
}

int partition2p (int *a, int l, int r) {
  int i,j,pivot;
    // pivot (Element to be placed at right position)
    pivot = a[r];  
 
    i = (l - 1);  // Index of smaller element

    for (j = l; j <= r - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (a[j] <= pivot) {
            i++;    // increment index of smaller element
            swap(&(a[i]), &(a[j]));
        }
    }
    swap(&(a[i+1]), &(a[r]));
    return (i + 1);
}



void exch (int *a, int i, int j) {
  int tmp;
  tmp = a[i]; a[i] = a[j]; a[j] = tmp;
}

void quicksort3p(int *a, int l, int r)
{
  if (r<=l) return;

  int i = l-1, j = r;
  int p = l-1, q = r;

  while(1)
    {
      while (a[++i] < a[r]);

      while (a[r] < a[--j])
	if (j==l)
	  break;

      if(i>=j) break;

      exch(a, i, j);
      if(a[i] == a[r]) exch(a, ++p, i);
      if(a[j] == a[r]) exch(a, --q, j);
    }

  exch(a, i , r);
  j = i-1;
  i = i+1;
  for (int k = 1; k<=p; k++) exch(a, k, j--);
  for (int k = r-1; k>=q; k--) exch(a, k, i++);
  quicksort3p(a, l, j);
  quicksort3p(a, i, r);
}


int compareInt(int a, int b) {
  
}


int main()
{

  b = malloc(sizeof(int)*(ARR_SIZE));
  a = malloc(sizeof(int)*(ARR_SIZE));

  clock_t begin, end;

  randomArr(b, ARR_SIZE);

  copyArr(b, a);
  begin = clock();
  quicksort2p(a, 0, ARR_SIZE);
  end = clock();
  printf("2 partition time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
  
  copyArr(b, a);
  begin = clock();
  quicksort3p(a, 0, ARR_SIZE);
  end = clock();
  printf("3 partition time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);

  copyArr(b, a);
  begin = clock();
  qsort(a, ARR_SIZE, sizeof(int), compareInt);
  end = clock();
  printf("3 partition time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
  
  return 0;
}

