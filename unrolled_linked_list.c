#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int *data;
	struct node *next;
} node;

typedef struct {
	size_t size;
	size_t node_count;
	size_t node_size;
	node *head;
} unrolled_list;

node *make_node(size_t node_size)
{
	node *n = malloc(sizeof(node));
	n->data = malloc(sizeof(int) * node_size);
	n->next = NULL;
	return n;
}

unrolled_list make_list(size_t node_size)
{
	unrolled_list list = {
		.size = 0,
		.node_count = 0,
		.node_size = node_size,
		.head = NULL
	};
	return list;
}

void free_list(unrolled_list l) {
	node *ptr = l.head;
	while(ptr != NULL) {
		node *next = ptr->next;
		free(ptr->data);
		free(ptr);
		ptr = next;
	}
}

node* get_node(unrolled_list l, size_t index)
{
	node *ptr = l.head;
	for(size_t i = 0; i < index && ptr != NULL; ++i, ptr = ptr->next);
	return ptr;
}

void append_node(unrolled_list *l)
{
	l->node_count++;
	if(l->head == NULL) {
		l->head = make_node(l->node_size);
		return;
	}
	node *ptr = l->head;
	while(ptr->next != NULL) ptr = ptr->next;
	ptr->next = make_node(l->node_size);
}

int get(unrolled_list l, size_t index)
{
	node* n = get_node(l, index / l.node_count);
	if(n == NULL) return 0;
	return n->data[index % l.node_count];
}

void set(unrolled_list l, size_t index, int value)
{
	node *n = get_node(l, index / l.node_size);
	if(n == NULL) return;
	n->data[index % l.node_size] = value;
}

void push(unrolled_list *l, int value)
{
	if(l->size == l->node_size * l->node_count) {
		append_node(l);
	}
	set(*l, l->size++, value);
}

void print_list(unrolled_list l) 
{
	size_t i = 0;
	printf("[ ");
	for(node *ptr = l.head; ptr != NULL; ptr = ptr->next) {
		for(int j = 0; j < l.node_size; ++j) {
			if(i >= l.size) break;
			printf("%d ", ptr->data[j]);
			++i;
		}
	}
	printf("]\n");
}

void print_arr(int *arr, size_t len)
{
	printf("[ ");
	for(size_t i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	printf("]\n");
}

int main(void)
{

	unrolled_list list = make_list(10);
	append_node(&list);
	append_node(&list);

	for(int i = 0; i < 15; ++i) {
		push(&list, i);
	}

	print_list(list);

	return 0;
}