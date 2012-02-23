/*
 *
 * Parallel bottom-up merge sort algorithm in C-OpenMP.
 *
 *
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 4

int min(int a, int b) {
  return a < b ? a : b;
}

void merge(int* a, int* temp, int left, int m, int right) {
  int i, j, k;
  for(i = m+1; i > left; i--) temp[i-1] = a[i-1];
  for(j = m; j < right; j++) temp[right+m-j] = a[j+1];
  for(k = left; k <= right; k++) {
    if(temp[j] < temp[i]) a[k] = temp[j--];
    else a[k] = temp[i++];
  }
}

int* merge_sort(int* a, int left, int right) {
  if(left < right) {
    int temp[SIZE];
    int m, i;
    for(m = 1; m <= right - left; m += m) {
      for(i = left; i <= right - m; i += m+m)
        merge(a, temp, i, i+m-1, min(i+m+m-1, right));
    }
  }
  return a;
}

void parallel_merge_sort(int* a) {
  int n = SIZE >> 1;
  int left = n+1;
  int right = (SIZE - left) + 1;
#pragma omp sections
  {
#pragma omp section
    merge_sort(a, 0, left);
#pragma omp section
    merge_sort(a, left, right);
  }
}

void display(int* a) {
  int i;
  for(i = 0; i < SIZE; i++)
    printf("%d ", a[i]);
  printf("\n");
}

int is_sorted(int* a) {
  int i;
  for(i = 1; i < SIZE; i++)
    if(a[i] < a[i-1]) return 0;
  return 1;
}

int main (int argc, char const *argv[]) {
  
  int a[SIZE];
  
  a[0] = 42321;
  a[1] = 32;
  a[2] = 1;
  a[3] = 132131;
  
  display(a);
  parallel_merge_sort(a);
  display(a);
  printf("is_sorted: %d\n", is_sorted(a));
  
  return 0;
}
