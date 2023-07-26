#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
	struct node *prev;
} node;

typedef struct {
	size_t size;
	node *head;
	node *tail;
} doubly_list;

node *make_node(int value)
{
	node *n = malloc(sizeof(node));
	n->value = value;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

doubly_list make_list()
{
	doubly_list list = {
		.size = 0,
		.head = NULL,
		.tail = NULL
	};
	return list;
}

void append(doubly_list *l, int value)
{
	if(l->size++ == 0) {
		node *n = make_node(value);
		l->head = n;
		l->tail = n;
		return;
	}
	node *n = make_node(value);
	n->prev = l->tail;
	l->tail->next = n;
	l->tail = l->tail->next;
}

void push(doubly_list *l, int value)
{
	if(l->size++ == 0) {
		node *n = make_node(value);
		l->head = n;
		l->tail = n;
		return;
	}

	node *n = make_node(value);
	n->next = l->head;
	l->head = n;
}

int pop_last(doubly_list *l)
{
	if(l->size < 1) return 0;
	int val = l->tail->value;
	l->tail = l->tail->prev;
	l->tail->next = NULL;
	l->size--;
	return val;
}

int pop(doubly_list *l)
{
	if(l->size < 1) return 0;
	int val = l->head->value;
	l->head = l->head->next;
	l->head->prev = NULL;
	l->size--;
	return val;
}

void print_list(doubly_list l)
{
	printf("[ ");
	for(node *ptr = l.head, *prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next) {
		printf("%d ", ptr->value);
	}
	printf("]\n");
}

int main(void)
{

	doubly_list list = make_list();
	print_list(list);

	append(&list, 10);
	print_list(list);

	push(&list, 20);
	print_list(list);

	append(&list, 30);
	print_list(list);

	pop(&list);
	print_list(list);

	pop_last(&list);
	print_list(list);

	return 0;
}