#include <stdio.h>
#include <stdlib.h>  // atoi

void ranges(int x[], int npts, int *max_ptr, int *min_ptr) {
  if (npts > 0) {
    // Execute only if npts is positive.
    *max_ptr = *min_ptr = x[0];

    int i;
    for (i = 0; i < npts; i++) {
      if (x[i] > *max_ptr) {
        *max_ptr = x[i];
      }
      if (x[i] < *min_ptr) {
        *min_ptr = x[i];
      }
    }
  }
}

int main(int argc, char **argv) {
  int arr[argc - 1];

  int i;
  for (i = 0; i < argc-1; i++) {
    arr[i] = atoi(argv[i+1]);
  }

  int min, max;
  ranges(arr, argc-1, &max, &min);

  printf("MIN: %d\n", min);
  printf("MAX: %d\n", max);

  return 0;
}
