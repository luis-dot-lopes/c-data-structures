#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
} node;

typedef struct {
	size_t size;
	node *head;
} linked_list;

node *make_node(int value)
{
	node *n = malloc(sizeof(node));
	n->value = value;
	n->next = NULL;
	return n;
}

linked_list make_list()
{
	linked_list list = {
		.size = 0,
		.head = NULL
	};
	return list;
}

void free_list(linked_list l) {
	node *ptr = l.head;
	while(ptr != NULL) {
		node *next = ptr->next;
		free(ptr);
		ptr = next;
	}
}

void append(linked_list *l, int value)
{
	l->size++;
	if(l->head == NULL) {
		l->head = make_node(value);
		return;
	}
	node *ptr = l->head;
	while(ptr->next != NULL) ptr = ptr->next;
	ptr->next = make_node(value);
}

void push(linked_list *l, int value)
{
	l->size++;
	node *n = make_node(value);
	n->next = l->head;
	l->head = n;
}

int pop_last(linked_list *l)
{
	if(l->size < 1) return 0;
	node *ptr = l->head, *prev = NULL;
	while(ptr->next != NULL) prev = ptr, ptr = ptr->next;
	int val = ptr->value;
	prev->next = NULL;
	return val;
}

int pop(linked_list *l)
{
	if(l->size < 1) return 0;
	node *n = l->head->next;
	int val = l->head->value;
	l->head = n;
	l->size--;
	return val;
}

int get(linked_list l, size_t index)
{
	node *ptr = l.head;
	for(size_t i = 0; i < index && ptr != NULL; ++i, ptr = ptr->next);
	if(ptr == NULL) {
		return 0;
	} else {
		return ptr->value;
	}
}

void set(linked_list l, size_t index, int value)
{
	node *ptr = l.head;
	for(size_t i = 0; i < index && ptr != NULL; ++i, ptr = ptr->next);
	if(ptr == NULL) {
		return;
	} else {
		ptr->value = value;
	}
}

void print_list(linked_list l)
{
	printf("[ ");
	for(node *ptr = l.head, *prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next) {
		printf("%d ", ptr->value);
	}
	printf("]\n");
}

int main(void)
{
	linked_list list = make_list();
	print_list(list);

	append(&list, 10);
	print_list(list);

	append(&list, 20);
	print_list(list);

	push(&list, 30);
	print_list(list);

	for(int i = 0; i < list.size; ++i)
		printf("%d\n", get(list, i));

	set(list, 1, 40);
	print_list(list);

	pop(&list);
	print_list(list);

	pop_last(&list);
	print_list(list);

	free_list(list);

	return 0;
}
