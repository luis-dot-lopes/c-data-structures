#include <stdio.h>

/*
This function takes an element and a sorted array.
It then returns the index at which such element would have to
be inserted such that the array remains sorted.
Thus, if the element is in the array, the index of its first ocurrence is
returned.
*/
size_t
binary_search(int elem, int* arr, size_t arr_len)
{
  size_t upper = arr_len - 1;
  size_t lower = 0;
  size_t middle = (upper + lower) / 2;
  while (middle > 0 && middle < arr_len && lower <= upper) {
    if (elem <= arr[middle])
      upper = middle - 1;
    if (elem > arr[middle])
      lower = middle + 1;
    middle = (upper + lower) / 2;
  }
  return lower;
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
main(int argc, char const* argv[])
{

  int arr[] = { 1, 1, 2, 2, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
  size_t arr_len = sizeof(arr) / sizeof(int);

  size_t index = binary_search(10, arr, arr_len);
  print_arr(arr, arr_len);
  printf("%d\n", index);

  return 0;
}
