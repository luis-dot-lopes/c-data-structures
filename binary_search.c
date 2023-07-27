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
  size_t index = arr_len / 2;
  while (index > 0 && index < arr_len &&
         !(arr[index - 1] < elem && elem <= arr[index])) {
    if (elem <= arr[index])
      index /= 2;
    if (elem > arr[index])
      index = (arr_len + index + 1) / 2;
  }
  return index;
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

  int arr[] = { 1, 1, 2, 2, 2, 3, 6 };
  size_t arr_len = sizeof(arr) / sizeof(int);

  size_t index = binary_search(6, arr, arr_len);
  print_arr(arr, arr_len);
  printf("%d\n", index);

  return 0;
}
