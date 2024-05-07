#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  size_t i;
  size_t j;
} Comp;

typedef struct
{
  int* new_state;
  size_t size_state;
} Change;

union step_type
{
  Comp comp;
  Change change;
};

enum step_tag
{
  COMP,
  CHANGE
};

typedef struct
{
  enum step_tag tag;
  union step_type type;
} Step;

typedef struct
{
  Step* items;
  size_t size;
  size_t cap;
} Steps;

void
add_change(Steps* steps, int* state, size_t size)
{
  Change change = { 0 };
  change.size_state = size;
  int* new_state = malloc(sizeof(state[0]) * size);
  memcpy(new_state, state, sizeof(state[0]) * size);
  change.new_state = new_state;
  if (steps->size == steps->cap) {
    steps->cap = 2 * steps->cap + 1;
    steps->items = realloc(steps->items, steps->cap * sizeof(steps->items[0]));
  }
  steps->items[steps->size].tag = CHANGE;
  steps->items[steps->size++].type.change = change;
}

void
add_comp(Steps* steps, size_t i, size_t j)
{
  Comp comp = { .i = i, .j = j };
  if (steps->size == steps->cap) {
    steps->cap = 2 * steps->cap + 1;
    steps->items = realloc(steps->items, steps->cap * sizeof(steps->items[0]));
  }
  steps->items[steps->size].tag = COMP;
  steps->items[steps->size++].type.comp = comp;
}

void
insertion_sort(int* arr, size_t arr_len, Steps* steps)
{

  add_change(steps, arr, arr_len);

  for (size_t i = 1; i < arr_len; ++i) {
    int key = arr[i];
    size_t j = i;
    for (; j-- > 0 && arr[j] > key;) {
      add_comp(steps, j, i);
    }
    memcpy(&arr[j + 2], &arr[j + 1], sizeof(int) * (i - j - 1));
    arr[j + 1] = key;

    add_change(steps, arr, arr_len);
  }
}

void
bubble_sort(int* arr, size_t arr_len, Steps* steps)
{
  add_change(steps, arr, arr_len);

  for (size_t i = 0; i < arr_len - 1; ++i) {
    for (size_t j = i + 1; j < arr_len; ++j) {
      add_comp(steps, i, j);
      if (arr[i] > arr[j]) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        add_change(steps, arr, arr_len);
      }
    }
  }
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
main(void)
{

  const int screen_width = 800;
  const int screen_height = 600;

  const int rect_width = 40;
  const int height_unit = 40;
  const int padding = 3;
  const int margin = 100;
  const int base = screen_height * 2 / 3;

  int values[] = { 1, 2, 6, 5, 3, 4, 7 };
  size_t value_count = sizeof(values) / sizeof(values[0]);

  const int start_x =
    screen_width / 2 - ((rect_width + padding) * value_count - padding) / 2;

  size_t j = 0;

  InitWindow(screen_width, screen_height, "raylib");

  SetTargetFPS(60);

  Steps steps = { 0 };
  bubble_sort(values, value_count, &steps);

  int* to_display = NULL;
  size_t to_display_size = 0;

  while (!WindowShouldClose()) {

    if (IsKeyPressed(KEY_N) && j < steps.size - 1) {
      ++j;
      TraceLog(LOG_INFO, "Next state %d, %d", j, steps.items[j].tag);
    } else if (IsKeyPressed(KEY_P) && j > 0) {
      --j;
      TraceLog(LOG_INFO, "Previous state %d, %d", j, steps.items[j].tag);
    }

    BeginDrawing();
    {
      ClearBackground(BLACK);

      size_t c1 = to_display_size, c2 = to_display_size;
      if (steps.items[j].tag == CHANGE) {
        Change change = steps.items[j].type.change;
        if (to_display == NULL || to_display_size < change.size_state) {
          to_display_size = change.size_state;
          if (to_display != NULL) {
            free(to_display);
          }
          to_display = malloc(sizeof(to_display[0]) * to_display_size);
        }
        memcpy(to_display,
               change.new_state,
               to_display_size * sizeof(to_display[0]));
      } else if (steps.items[j].tag == COMP) {
        Comp comp = steps.items[j].type.comp;
        c1 = comp.i, c2 = comp.j;
      }

      for (size_t i = 0; i < to_display_size; ++i) {
        DrawRectangle(start_x + (rect_width + padding) * i,
                      base - to_display[i] * height_unit,
                      rect_width,
                      height_unit * to_display[i],
                      (c1 == i || c2 == i) ? RED : WHITE);
      }
    }
    EndDrawing();
  }
  return 0;
}
