#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H
typedef struct string_vector {
  char **lines;
  int numlines;
  int capacity;
} string_vector;

string_vector *new_string_vector();
void string_vector_push(string_vector *, const char *);
void free_string_vector(string_vector *);
#endif
