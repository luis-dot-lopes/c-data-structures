#include <stdio.h>
#include <stdlib.h>

#define STACK_CAP 100

// Array based stack implementation
typedef struct
{
  int data[STACK_CAP];
  size_t size;
} stack_array;

// The functions do not implement error handling
void
push_stack_array(stack_array* stack, int elem)
{
  stack->data[stack->size++] = elem;
}

int
pop_stack_array(stack_array* stack)
{
  return stack->data[--stack->size];
}

int
peek_stack_array(stack_array* stack)
{
  return stack->data[stack->size - 1];
}

int
empty_stack_array(stack_array* stack)
{
  return stack->size == 0;
}

// Headless linked list based stack
typedef struct node
{
  int value;
  struct node* next;
} node;

node*
make_list(int value)
{
  node* n = malloc(sizeof(node));
  n->value = value;
  return n;
}

void
push_stack_nhll(node** stack, node* x)
{
  x->next = *stack;
  *stack = x;
}

node*
pop_stack_nhll(node** stack)
{
  node* n = *stack;
  *stack = (*stack)->next;
  n->next = NULL;
  return n;
}

int
peek_stack_nhll(node** stack)
{
  return (*stack)->value;
}

int
empty_stack_nhll(node** stack)
{
  return *stack == NULL;
}

// Implementation based on linked list with a head
typedef struct
{
  size_t size;
  node* head;
} stack_ll;

void
push_stack_hll(stack_ll* stack, int x)
{
  node* n = make_node(x);
  n->next = stack->head;
  stack->head = n;
  stack->size++;
}

int
pop_stack_hll(stack_ll* stack)
{
  int x = stack->head->value;
  node* n = stack->head;
  stack->head = stack->head->next;
  free(n);
  stack->size--;
  return x;
}

int
peek_stack_hll(stack_ll* stack)
{
  return stack->head->value;
}

int
empty_stack_hll(stack_ll* stack)
{
  return stack->head == NULL;
}