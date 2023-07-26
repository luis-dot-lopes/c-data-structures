#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int *data;
	size_t size;
	size_t cap;
} dyn_array;

dyn_array make_array(size_t init_cap)
{
	dyn_array arr = {0};
	init_cap = init_cap < 1 ? 1 : init_cap;
	arr.data = malloc(init_cap * sizeof(int));
	arr.size = 0;
	arr.cap = init_cap;
	return arr;
}

void free_array(dyn_array arr) 
{
	free(arr.data);
}

//no bounds check
int get(dyn_array arr, size_t index)
{
	return arr.data[index];
}

void set(dyn_array *arr, size_t index, int value)
{
	arr->data[index] = value;
}

void add(dyn_array *arr, int value)
{
	if(arr->size == arr->cap) {
		arr->data = realloc(arr->data, arr->cap * 2 * sizeof(int));
		arr->cap *= 2;
	}
	arr->data[arr->size++] = value;
}

void insert(dyn_array *arr, size_t index, int value)
{
	if(arr->size == arr->cap) {
		arr->data = realloc(arr->data, arr->cap * 2 * sizeof(int));
		arr->cap *= 2;
	}
	memmove(arr->data + index + 1, arr->data + index, (arr->size - index) * sizeof(int));
	arr->data[index] = value;
	arr->size++;
}

int pop(dyn_array *arr)
{
	if(arr->size < 1) return 0;
	if(arr->size < arr->cap / 4) {
		arr->data = realloc(arr->data, arr->cap / 4 * sizeof(int));
		arr->cap /= 4;
	}
	return arr->data[--arr->size];
}

int delete(dyn_array *arr, size_t index)
{
	if(arr->size < 1) return 0;
	if(arr->size < arr->cap / 4) {
		arr->data = realloc(arr->data, arr->cap / 4 * sizeof(int));
		arr->cap /= 4;
	}
	int result = arr->data[index];
	memmove(arr->data + index, arr->data + index + 1, (arr->size - index) * sizeof(int));
	arr->size--;
	return result;
}

void print_arr(dyn_array arr)
{
	printf("[ ");
	for(size_t i = 0; i < arr.size; ++i) {
		printf("%d ", arr.data[i]);
	}
	printf("]\n");
}

int main(void)
{
	dyn_array arr = make_array(1);

	for(int i = 0; i < 10; ++i) {
		add(&arr, i);
	}

	printf("%d %d\n", arr.size, arr.cap);
	print_arr(arr);

	for(int i = 0; i < 2; ++i) {
		pop(&arr);
	}

	printf("%d %d\n", arr.size, arr.cap);
	print_arr(arr);

	delete(&arr, 1);

	printf("%d %d\n", arr.size, arr.cap);
	print_arr(arr);

	free_array(arr);

	return 0;
}