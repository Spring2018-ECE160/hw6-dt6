#include <stdio.h>
#include <string_vector.h>
#define MAX_LINE_LENGTH 1024

// Quick sort lines using predicate comp.
void qsort(char **lines, int left, int right, int direction,
           int (*comp)(const char *, const char *));

// Swap two elements in array.
void swap(void **arr, int index1, int index2);

// Case-sensitive
int sensitive_comp(const char *, const char *);

// Case-insensitive
int insensitive_comp(const char *, const char *);

void read_file(const char *filename, string_vector *v);

int main(int argc, char **argv) {
  string_vector *v = new_string_vector();
  int direction = 1;
  int sensitive = 1;

  int i;
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'r') {
        direction = -1;
      } else if (argv[i][1] == 'f') {
        sensitive = 0;
      }
    } else {
      read_file(argv[i], v);
    }
  }

  qsort(v->lines, 0, v->numlines - 1, direction,
        sensitive ? sensitive_comp : insensitive_comp);

  for (i = 0; i < v->numlines; i++) {
    printf("%s", v->lines[i]);
  }

  free_string_vector(v);
  return 0;
}

void qsort(char **lines, int left, int right, int direction,
           int (*comp)(const char *, const char *)) {
  int i, last;

  if (left >= right) {  // do nothing if array contains
    return;             // fewer than two elements.
  }

  swap((void **)lines, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if ((*comp)(lines[i], lines[left]) * direction < 0) {
      swap((void **)lines, ++last, i);
    }
  }
  swap((void **)lines, left, last);

  qsort(lines, left, last - 1, direction, comp);
  qsort(lines, last + 1, right, direction, comp);
}

void swap(void **arr, int index1, int index2) {
  void *temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}

int sensitive_comp(const char *str1, const char *str2) {
  if (*str1 == '\0' && *str2 == '\0') {
    return 0;
  } else if (*str1 == '\0') {
    return -1;
  } else if (*str2 == '\0') {
    return 1;
  } else if (*str1 == *str2) {
    return sensitive_comp(str1 + 1, str2 + 1);
  } else {
    return *str1 - *str2;
  }
}

int insensitive_comp(const char *str1, const char *str2) {
  char c1 = *str1 >= 'a' && *str1 <= 'z' ? *str1 + 'A' - 'a' : *str1;
  char c2 = *str2 >= 'a' && *str2 <= 'z' ? *str2 + 'A' - 'a' : *str2;

  if (c1 == '\0' && c2 == '\0') {
    return 0;
  } else if (c1 == '\0') {
    return -1;
  } else if (c2 == '\0') {
    return 1;
  } else if (c1 == c2) {
    return insensitive_comp(str1 + 1, str2 + 1);
  } else {
    return c1 - c2;
  }
}

void read_file(const char *filename, string_vector *v) {
  FILE *file = fopen(filename, "r");
  char line[MAX_LINE_LENGTH];

  if (file != NULL) {
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
      string_vector_push(v, line);
    }

    fclose(file);
  }
}
