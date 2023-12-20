#include <raylib.h>
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

void
draw_tree(int x, int y, int radius, int width, int y_offset, Tree* tree)
{
  if (tree == NULL)
    return;

  if (tree->left != NULL) {
    DrawLine(x, y, x - width / 4, y + y_offset, RED);
  }

  if (tree->right != NULL) {
    DrawLine(x, y, x + width / 4, y + y_offset, RED);
  }

  DrawCircle(x, y, radius, LIGHTGRAY);
  char buffer[20];
  itoa(tree->value, buffer, 10);
  DrawText(buffer, x - 2, y - 2, 12, BLACK);

  if (tree->left != NULL) {
    draw_tree(
      x - width / 4, y + y_offset, radius, width / 2, y_offset, tree->left);
  }

  if (tree->right != NULL) {
    draw_tree(
      x + width / 4, y + y_offset, radius, width / 2, y_offset, tree->right);
  }
}

int
main(void)
{

  const int screen_width = 800;
  const int screen_height = 600;

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

  InitWindow(screen_width, screen_height, "raylib");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(BLACK);
      int height = 5;
      int node_radius = 10;
      draw_tree(screen_width / 2, 12, node_radius, screen_width, 56, tree);
    }
    EndDrawing();
  }

  return 0;
}
