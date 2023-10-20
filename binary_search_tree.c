#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
  int value;
  struct tree* left;
  struct tree* right;
} Tree;

Tree*
make_tree(int value)
{
  Tree* tree = malloc(sizeof(Tree));
  tree->value = value;
  tree->left = NULL;
  tree->right = NULL;
}

void
delete_tree(Tree* tree)
{
  if (tree == NULL)
    return;
  delete_tree(tree->right);
  delete_tree(tree->left);
  free(tree);
}

void
insert_key(Tree* tree, int val)
{
  if (tree == NULL)
    return;
  Tree* current_node = tree;
  while (current_node != NULL) {
    if (val > current_node->value) {
      if (current_node->right == NULL) {
        current_node->right = make_tree(val);
        return;
      }
      current_node = current_node->right;
    } else if (val < current_node->value) {
      if (current_node->left == NULL) {
        current_node->left = make_tree(val);
        return;
      }
      current_node = current_node->left;
    } else {
      return;
    }
  }
}

Tree*
search_key(Tree* tree, int val)
{
  Tree* current_node = tree;
  while (current_node != NULL) {
    if (val > current_node->value) {
      current_node = current_node->right;
    } else if (val < current_node->value) {
      current_node = current_node->left;
    } else {
      break;
    }
  }
  return current_node;
}

Tree*
minimum(Tree* tree)
{
  Tree* previous_node = NULL;
  Tree* current_node = tree;
  while (current_node != NULL) {
    previous_node = current_node;
    current_node = current_node->left;
  }
  return previous_node;
}

void
delete_key(Tree* tree, int val)
{
  Tree* previous_node = NULL;
  Tree* current_node = tree;
  while (current_node != NULL && current_node->value != val) {
    previous_node = current_node;
    if (val > current_node->value) {
      current_node = current_node->right;
    } else if (val < current_node->value) {
      current_node = current_node->left;
    }
  }
  if (current_node == NULL)
    return;
  if (current_node->right == NULL) {
    if (val < previous_node->value) {
      previous_node->left = current_node->left;
    } else {
      previous_node->right = current_node->left;
    }
    current_node->left = NULL;
    delete_tree(current_node);
  } else {
    Tree* min_parent = current_node;
    Tree* min = current_node->right;
    while (min->left != NULL) {
      min_parent = min;
      min = min->left;
    }
    min_parent->left = min->right;
    min->left = current_node->left;
    if (min_parent != current_node) {
      min->right = current_node->right;
    }
    if (val < previous_node->value) {
      previous_node->left = min;
    } else {
      previous_node->right = min;
    }
    current_node->left = NULL;
    current_node->right = NULL;
    delete_tree(current_node);
  }
}

void
print_tree(Tree* tree, size_t depth)
{
  if (tree == NULL)
    return;
  for (size_t i = 0; i < 2 * depth; ++i) {
    putchar(' ');
  }
  printf("%d\n", tree->value);
  print_tree(tree->right, depth + 1);
  print_tree(tree->left, depth + 1);
}

int
main(int argc, char const* argv[])
{

  Tree* tree = make_tree(8);

  insert_key(tree, 3);
  insert_key(tree, 6);
  insert_key(tree, 1);
  insert_key(tree, 4);
  insert_key(tree, 7);
  insert_key(tree, 10);
  insert_key(tree, 14);
  insert_key(tree, 13);
  insert_key(tree, 5);

  print_tree(tree, 0);

  delete_key(tree, 3);

  print_tree(tree, 0);

  delete_tree(tree);

  return 0;
}
