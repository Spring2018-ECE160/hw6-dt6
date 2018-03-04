#include <queue.h>
#include <stdio.h>
#include <stdlib.h>  // atoi
#define DEFAULT_N 10

int main(int argc, char **argv) {
  FILE *file;
  int n;
  int n_is_given = 0;          // Flag to check if number of lines is given.
  char line[MAX_LINE_LENGTH];  // Variable to hold a line from file.

  // Queue to hold lines.
  queue q;
  init_queue(&q);

  int i;
  for (i = 1; i < argc; i++) {
    switch (argv[i][0]) {
      case '-':
        // Number of lines.
        n = atoi(argv[i] + 1);
        n_is_given = 1;
        break;
      default:
        // Open file in read mode.
        file = fopen(argv[i], "r");
        if (file == NULL) {
          // Failed to open file.
          return 1;
        }
        break;
    }
  }

  if (!n_is_given) {
    n = DEFAULT_N;
  }

  // Read file.
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    enqueue(&q, line);
    if (q.size > n) {
      dequeue(&q);
    }
  }

  // Print the last n lines.
  while (q.size != 0) {
    printf("%s", peek(&q));
    dequeue(&q);
  }

  fclose(file);

  return 0;
}
