#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define B 0
#define R 1

typedef struct node
{
  int value;
  int color;
  struct node* parent;
  struct node* left;
  struct node* right;
} Node;

typedef struct rb_tree
{
  Node* root;
  Node* null;
} RBTree;

Node*
alloc_node(int value, int color, Node* parent, Node* left, Node* right)
{
  Node* new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->color = color;
  new_node->parent = parent;
  new_node->left = left;
  new_node->right = right;
  return new_node;
}

RBTree*
alloc_tree()
{
  RBTree* new_tree = malloc(sizeof(RBTree));
  Node* null = malloc(sizeof(Node));
  null->value = 0;
  null->color = B;
  null->parent = null;
  null->left = null;
  null->right = null;
  new_tree->null = null;
  new_tree->root = null;
  return new_tree;
}

void
delete_subtree(RBTree* tree, Node* node)
{
  if (node == tree->null)
    return;
  delete_subtree(tree, node->left);
  delete_subtree(tree, node->right);
  free(node);
}

void
delete_tree(RBTree* tree)
{
  if (tree->root != tree->null) {
    delete_subtree(tree, tree->root);
  }
  free(tree->null);
  free(tree);
}

Node*
search_key(RBTree* tree, int value)
{
  Node* current_node = tree->root;
  while (current_node != tree->null) {
    if (current_node->value == value) {
      break;
    } else if (current_node->value > value) {
      current_node = current_node->left;
    } else {
      current_node = current_node->right;
    }
  }
  return current_node;
}

void
left_rotation(RBTree* tree, Node* x)
{
  Node* y = x->right;
  x->right = y->left;
  if (y->left != tree->null) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == tree->null) {
    tree->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void
right_rotation(RBTree* tree, Node* y)
{
  Node* x = y->left;
  y->left = x->right;
  if (x->right != tree->null) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == tree->null) {
    tree->root = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

void
fix_insertion(RBTree* tree, Node* z)
{
  while (z->parent->color == R) {
    if (z->parent == z->parent->parent->left) {
      Node* y = z->parent->parent->right;
      if (y->color == R) {
        z->parent->color = B;
        y->color = B;
        z = y->parent;
        z->color = R;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotation(tree, z);
        }
        z->parent->color = B;
        z->parent->parent->color = R;
        right_rotation(tree, z->parent->parent);
      }
    } else {
      Node* y = z->parent->parent->left;
      if (y->color == R) {
        z->parent->color = B;
        y->color = B;
        z = y->parent;
        z->color = R;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotation(tree, z);
        }
        z->parent->color = B;
        z->parent->parent->color = R;
        left_rotation(tree, z->parent->parent);
      }
    }
  }
  tree->root->color = B;
}

void
insert_key(RBTree* tree, int value)
{
  if (tree->root == tree->null) {
    Node* new_node = alloc_node(value, B, tree->null, tree->null, tree->null);
    tree->root = new_node;
    return;
  }
  Node* parent = tree->null;
  Node* current_node = tree->root;
  while (current_node != tree->null) {
    parent = current_node;
    if (current_node->value > value) {
      current_node = current_node->left;
    } else {
      current_node = current_node->right;
    }
  }

  Node* new_node = alloc_node(value, R, parent, tree->null, tree->null);
  if (parent->value > value) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  fix_insertion(tree, new_node);
}

void
draw_subtree(int x,
             int y,
             int radius,
             int width,
             int y_offset,
             RBTree* tree,
             Node* node)
{
  if (node == tree->null)
    return;

  if (node->left != tree->null) {
    DrawLine(x, y, x - width / 4, y + y_offset, BLACK);
  }

  if (node->right != tree->null) {
    DrawLine(x, y, x + width / 4, y + y_offset, BLACK);
  }

  if (node->color == R) {
    DrawCircle(x, y, radius, RED);
  } else {
    DrawCircle(x, y, radius, BLACK);
  }

  char buffer[20];
  itoa(node->value, buffer, 10);
  int text_offset = MeasureText(buffer, 12);
  DrawText(buffer, x - text_offset / 2, y - 2, 12, WHITE);

  if (node->left != tree->null) {
    draw_subtree(x - width / 4,
                 y + y_offset,
                 radius,
                 width / 2,
                 y_offset,
                 tree,
                 node->left);
  }

  if (node->right != tree->null) {
    draw_subtree(x + width / 4,
                 y + y_offset,
                 radius,
                 width / 2,
                 y_offset,
                 tree,
                 node->right);
  }
}

int
main(void)
{
  RBTree* tree = alloc_tree();

  insert_key(tree, 1);
  insert_key(tree, 2);
  insert_key(tree, 3);
  insert_key(tree, 4);
  insert_key(tree, 5);
  insert_key(tree, 6);

  const int screen_width = 800;
  const int screen_height = 600;

  InitWindow(screen_width, screen_height, "raylib");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(LIGHTGRAY);
      int height = 5;
      int node_radius = 10;
      draw_subtree(
        screen_width / 2, 12, node_radius, screen_width, 56, tree, tree->root);
    }
    EndDrawing();
  }

  delete_tree(tree);
}
