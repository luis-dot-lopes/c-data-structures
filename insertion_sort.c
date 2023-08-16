#include <stdio.h>
#include <string.h>

void
print_arr(int* arr, size_t arr_len)
{
  printf("[ ");
  for (size_t i = 0; i < arr_len; ++i) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}

void
insertion_sort(int* arr, size_t arr_len)
{
  for (size_t i = 1; i < arr_len; ++i) {
    int key = arr[i];
    size_t j = i - 1;
    for (; j >= 0 && arr[j] > key; --j)
      ;
    memcpy(&arr[j + 2], &arr[j + 1], sizeof(int) * (i - j - 1));
    arr[j + 1] = key;
  }
}

int
main(void)
{

  int arr[] = { 3, 2, 2, 1, 4, 5, 4 };
  size_t arr_len = sizeof(arr) / sizeof(int);

  print_arr(arr, arr_len);
  insertion_sort(arr, arr_len);
  print_arr(arr, arr_len);

  return 0;
}