#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// arr[end] is out of bounds
void
merge(int* arr, size_t start, size_t middle, size_t end, int* target)
{
  size_t i = start, j = middle, k = start;
  while (k < end) {
    if (j < end && (i >= middle || arr[j] < arr[i])) {
      target[k++] = arr[j++];
    } else {
      target[k++] = arr[i++];
    }
  }
}

// arr[end] is out of bounds
void
merge_sort(int* arr, size_t start, size_t end, int* target)
{
  size_t len = end - start;
  if (len < 2 || len > end)
    return;
  size_t middle = (start + end) / 2;
  merge_sort(arr, start, middle, target);
  merge_sort(arr, middle, end, target);
  merge(arr, start, middle, end, target);
  memcpy(arr + start, target + start, len * sizeof(target[0]));
}

void
print_arr(int* arr, size_t arr_len)
{
  printf("[ ");
  for (size_t i = 0; i < arr_len; ++i) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}

int
main(void)
{
  int arr[] = { 0, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9 };
  size_t arr_len = sizeof(arr) / sizeof(int);
  int arr2[arr_len];

  print_arr(arr, arr_len);
  merge_sort(arr, 0, arr_len, arr2);
  print_arr(arr2, arr_len);

  return 0;
}