#include <stdio.h>

void
selection_sort(int* arr, size_t arr_len)
{
  for (size_t i = 0; i < arr_len; ++i) {
    size_t min_idx = i;
    for (size_t j = i; j < arr_len; ++j) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    int tmp = arr[min_idx];
    arr[min_idx] = arr[i];
    arr[i] = tmp;
  }
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
  int arr[] = { 3, 2, 2, 1, 4, 5, 4 };
  size_t arr_len = sizeof(arr) / sizeof(int);

  print_arr(arr, arr_len);
  selection_sort(arr, arr_len);
  print_arr(arr, arr_len);

  return 0;
}
