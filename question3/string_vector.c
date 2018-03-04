#include <stdlib.h>
#include <string.h>
#include <string_vector.h>

string_vector *new_string_vector() {
  string_vector *v = malloc(sizeof(string_vector));
  v->lines = malloc(sizeof(char *));
  v->numlines = 0;
  v->capacity = 1;

  return v;
}

void string_vector_push(string_vector *v, const char *str) {
  if (v->numlines < v->capacity) {
    // There is space available.
    int len = strlen(str) + 1;
    v->lines[v->numlines] = malloc(sizeof(char) * len);
    strcpy(v->lines[v->numlines], str);
    v->numlines++;
  } else {
    // Double the capacity and retry.
    char **temp_lines = malloc(sizeof(char *) * v->capacity * 2);
    int i;
    for (i = 0; i < v->numlines; i++) {
      temp_lines[i] = v->lines[i];
    }
    free(v->lines);
    v->lines = temp_lines;
    v->capacity *= 2;

    string_vector_push(v, str);
  }
}

void free_string_vector(string_vector *v) {
  int i;
  for (i = 0; i < v->numlines; i++) {
    free(v->lines[i]);
  }
  free(v->lines);
  free(v);
}
