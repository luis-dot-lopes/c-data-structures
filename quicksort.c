#include <stdio.h>
#include <stdlib.h>

void
swap(int* x, int* y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

/*
This function sorts the array in the flowing way
elements lower than the pivot, then the pivot,
then elements greater than or equal to the pivot
The pivot is taken to be the first element.
The index at which the pivot ends up is returned.
*/
size_t
sort_pivot(int* arr, size_t arr_len)
{
  if (arr_len < 2)
    return 0;
  size_t pivot = 0;
  size_t point = arr_len - 1;
  size_t j = 1;
  for (; j <= point;) {
    if (arr[j] < arr[pivot])
      swap(arr + j, arr + pivot), pivot = j++;
    else
      swap(arr + j, arr + point--);
  }
  return pivot;
}

/*
This function applies the quicksort algorithm:
Call sort_pivot on the array, then call it again
on the elements less than the pivot and on the
elements less than the pivot.
*/
void
quicksort(int* arr, size_t arr_len)
{
  if (arr_len < 2)
    return;
  size_t pivot = sort_pivot(arr, arr_len);
  quicksort(arr, pivot);
  quicksort(arr + pivot + 1, arr_len - pivot - 1);
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
  quicksort(arr, arr_len);
  print_arr(arr, arr_len);

  return 0;
}
