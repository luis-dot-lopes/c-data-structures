#include <stdio.h>
#include <stdlib.h>

void
print_arr(int* arr, size_t arr_len);

void 
heap_sort(int *arr, size_t arr_len);

void
create_heap(int *arr, size_t arr_len);

void
sift_down(int *arr, size_t arr_len, size_t i);

int
remove_max(int *arr, size_t *arr_len);

void 
heap_sort(int *arr, size_t arr_len)
{
  size_t len = arr_len;
  create_heap(arr, arr_len);
  for(size_t i = arr_len - 1; i >= 1; --i) {
    arr[i] = remove_max(arr, &arr_len);
    //print_arr(arr, len);
  }
}

void
create_heap(int *arr, size_t arr_len)
{
  for(size_t i = (arr_len - 1) / 2; ; --i) {
    sift_down(arr, arr_len, i);
    if(i == 0) break;
  }
}

void
sift_down(int *arr, size_t arr_len, size_t i)
{
  int repeat = 1;
  size_t largest = 0;
  while(repeat) {
    size_t left = 2 * i + 1, right = 2 * i + 2;
    if(left < arr_len && arr[left] > arr[i]) {
      largest = left;
    } else {
      largest = i;
    }
    if(right < arr_len && arr[right] > arr[largest]) {
      largest = right;
    }
    if(largest != i) {
      int temp = arr[i];
      arr[i] = arr[largest];
      arr[largest] = temp;
      i = largest;
    } else {
      repeat = 0;
    }
  }
}

int
remove_max(int *arr, size_t *arr_len)
{
  int max = arr[0];
  arr[0] = arr[*arr_len - 1];
  *arr_len = *arr_len - 1;
  sift_down(arr, *arr_len, 0);
  return max;
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

  print_arr(arr, arr_len);
  heap_sort(arr, arr_len);
  print_arr(arr, arr_len);

  return 0;
}

