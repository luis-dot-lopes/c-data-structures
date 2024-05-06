#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  size_t (*comps)[2];
  size_t num_comps;
  size_t cap_comps;
} Comparisons;

typedef struct
{
  int** states;
  size_t num_states;
  size_t cap_states;
  size_t size_state;
} Swaps;

void
add_state(Swaps* a, int* state)
{
  int* new_state = malloc(sizeof(state[0]) * a->size_state);
  memcpy(new_state, state, sizeof(state[0]) * a->size_state);
  if (a->num_states == a->cap_states) {
    a->cap_states *= 2;
    a->states = realloc(a->states, a->cap_states * sizeof(a->states[0]));
  }
  a->states[a->num_states++] = new_state;
}

void
add_comp(Comparisons* cs, size_t i, size_t j)
{
  if (cs->num_comps == cs->cap_comps) {
    cs->cap_comps *= 2;
    cs->comps = realloc(cs->comps, cs->cap_comps * sizeof(cs->comps[0]));
  }
  cs->comps[cs->num_comps][0] = i;
  cs->comps[cs->num_comps++][1] = j;
}

void
insertion_sort(int* arr, size_t arr_len, Swaps* a, Comparisons* cs)
{
  a->size_state = arr_len;
  a->cap_states = arr_len;
  a->num_states = 0;
  a->states = malloc(sizeof(a->states[0]) * a->cap_states);

  cs->cap_comps = 1;
  cs->num_comps = 0;
  cs->comps = malloc(sizeof(cs->comps[0]) * cs->cap_comps);

  add_state(a, arr);
  add_comp(cs, arr_len, arr_len);

  for (size_t i = 1; i < arr_len; ++i) {
    int key = arr[i];
    size_t j = i;
    for (; j-- > 0 && arr[j] > key;) {
      add_state(a, arr);
      add_comp(cs, j, i);
    }
    memcpy(&arr[j + 2], &arr[j + 1], sizeof(int) * (i - j - 1));
    arr[j + 1] = key;

    add_state(a, arr);
    add_comp(cs, arr_len, arr_len);
  }
}

void
bubble_sort(int* arr, size_t arr_len, Swaps* a, Comparisons* cs)
{
  a->size_state = arr_len;
  a->cap_states = arr_len;
  a->num_states = 0;
  a->states = malloc(sizeof(a->states[0]) * a->cap_states);

  cs->cap_comps = 1;
  cs->num_comps = 0;
  cs->comps = malloc(sizeof(cs->comps[0]) * cs->cap_comps);

  add_state(a, arr);
  add_comp(cs, arr_len, arr_len);

  for (size_t i = 0; i < arr_len - 1; ++i) {
    for (size_t j = i + 1; j < arr_len; ++j) {
      add_state(a, arr);
      add_comp(cs, i, j);
      if (arr[i] > arr[j]) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
      add_state(a, arr);
      add_comp(cs, arr_len, arr_len);
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

  int values[] = { 7, 6, 5, 4, 3, 2, 1 };
  size_t value_count = sizeof(values) / sizeof(values[0]);

  const int start_x =
    screen_width / 2 - ((rect_width + padding) * value_count - padding) / 2;

  size_t j = 0;

  InitWindow(screen_width, screen_height, "raylib");

  SetTargetFPS(60);

  Swaps a = { 0 };
  Comparisons cs = { 0 };
  bubble_sort(values, value_count, &a, &cs);

  while (!WindowShouldClose()) {

    size_t c1 = cs.comps[j][0], c2 = cs.comps[j][1];

    if (IsKeyPressed(KEY_N) && j < a.num_states - 1) {
      ++j;
      TraceLog(LOG_INFO, "Next state %d", j);
      TraceLog(LOG_INFO, "Comparing %d and %d", c1, c2);
    } else if (IsKeyPressed(KEY_P) && j > 0) {
      --j;
      TraceLog(LOG_INFO, "Previous state %d", j);
      TraceLog(LOG_INFO, "Comparing %d and %d", c1, c2);
    }

    BeginDrawing();
    {
      ClearBackground(BLACK);

      for (size_t i = 0; i < a.size_state; ++i) {
        DrawRectangle(start_x + (rect_width + padding) * i,
                      base - a.states[j][i] * height_unit,
                      rect_width,
                      height_unit * a.states[j][i],
                      (c1 == i || c2 == i) ? RED : WHITE);
      }
    }
    EndDrawing();
  }
  return 0;
}
