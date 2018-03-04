#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 2048
#define NAME_FIELD_WIDTH 100
#define NUM_COLS 31

enum direction { NB, SB, EB, WB };

typedef struct date {
  int day;
  int month;
  int year;
} date;

typedef struct info {
  int segment_id;
  char roadway_name[NAME_FIELD_WIDTH];
  char from[NAME_FIELD_WIDTH];
  char to[NAME_FIELD_WIDTH];
  enum direction direction;
  date date;
  int hour;
  int traffic;
} info;

typedef struct infoset {
  info *info_array;
  int size;
  int capacity;
} infoset;

infoset *new_infoset();
void free_infoset(infoset *);
void infoset_push(infoset *, info);
infoset *infoset_from_csv(FILE *csv);
void infoset_dump(infoset *);
int busiest_hour(infoset *);
int average_traffic(infoset *s, const char *street_name, int hour);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: trafficanalysis <filename>\n");
    return 1;
  } else {
    FILE *file = fopen(argv[1], "r");
    if (file != NULL) {
      infoset *set = infoset_from_csv(file);
      printf("%d:00 is the busiest hour.\n", busiest_hour(set));
      printf("Average traffic of HUGUENOT AVE @ 15:00 is %d.\n",
             average_traffic(set, "HUGUENOT AVE", 15));
      free_infoset(set);
    }
  }
}

infoset *new_infoset() {
  infoset *s = malloc(sizeof(infoset));
  s->info_array = malloc(sizeof(info));
  s->size = 0;
  s->capacity = 1;

  return s;
}

void free_infoset(infoset *s) {
  free(s->info_array);
  free(s);
}

void infoset_push(infoset *s, info inf) {
  if (s->size < s->capacity) {
    // Info array has space available.
    s->info_array[s->size++] = inf;
  } else {
    // Double the capacity and retry.
    info *temp_info_array = malloc(sizeof(info) * s->capacity * 2);
    int i;
    for (i = 0; i < s->size; i++) {
      temp_info_array[i] = s->info_array[i];
    }
    free(s->info_array);
    s->info_array = temp_info_array;
    s->capacity *= 2;

    infoset_push(s, inf);
  }
}

infoset *infoset_from_csv(FILE *csv) {
  infoset *ret = new_infoset();

  char line[MAX_LINE_LENGTH];
  // Ignore Header.
  fgets(line, MAX_LINE_LENGTH, csv);
  while (fgets(line, MAX_LINE_LENGTH, csv) != NULL) {
    char *cols[NUM_COLS];
    int i, j;
    for (i = 0, j = 1, cols[0] = line; i < MAX_LINE_LENGTH && j < NUM_COLS;
         i++) {
      if (line[i] == ',') {
        line[i] = '\0';
        cols[j++] = &(line[i + 1]);
      }
    }

    // Push into infoset.
    int segment_id = atoi(cols[1]);
    char roadway_name[NAME_FIELD_WIDTH];
    strncpy(roadway_name, cols[2], NAME_FIELD_WIDTH);
    char from[NAME_FIELD_WIDTH];
    strncpy(from, cols[3], NAME_FIELD_WIDTH);
    char to[NAME_FIELD_WIDTH];
    strncpy(to, cols[4], NAME_FIELD_WIDTH);
    enum direction direction;
    if (strcmp("NB", cols[5]) == 0) {
      direction = NB;
    } else if (strcmp("SB", cols[5]) == 0) {
      direction = SB;
    } else if (strcmp("EB", cols[5]) == 0) {
      direction = EB;
    } else {
      direction = WB;
    }
    date date;
    cols[6][2] = '\0';
    cols[6][5] = '\0';
    date.month = atoi(cols[6]);
    date.day = atoi(cols[6] + 3);
    date.year = atoi(cols[6] + 6);
    for (i = 7; i < NUM_COLS; i++) {
      int hour = i - 7;
      int traffic = atoi(cols[i]);

      // Construct info
      info inf;
      inf.segment_id = segment_id;
      strncpy(inf.roadway_name, roadway_name, NAME_FIELD_WIDTH);
      strncpy(inf.from, from, NAME_FIELD_WIDTH);
      strncpy(inf.to, to, NAME_FIELD_WIDTH);
      inf.direction = direction;
      inf.date = date;
      inf.hour = hour;
      inf.traffic = traffic;

      // Push
      infoset_push(ret, inf);
    }
  }

  return ret;
}

void infoset_dump(infoset *s) {
  int i;
  for (i = 0; i < s->size; i++) {
    info *inf = &(s->info_array[i]);
    printf("%d,%s,%s,%s,%d,%d,%d,%d,%d,%d\n", inf->segment_id,
           inf->roadway_name, inf->from, inf->to, inf->direction,
           inf->date.year, inf->date.month, inf->date.day, inf->hour,
           inf->traffic);
  }
}

int busiest_hour(infoset *s) {
  int hours[24];
  int i;
  // Initialize array.
  for (i = 0; i < 24; i++) {
    hours[i] = 0;
  }
  // Count traffic.
  for (i = 0; i < s->size; i++) {
    hours[s->info_array[i].hour] += s->info_array[i].traffic;
  }
  // Find max.
  int ret = 0;
  for (i = 0; i < 24; i++) {
    if (hours[i] > hours[ret]) {
      ret = i;
    }
  }

  return ret;
}

int average_traffic(infoset *s, const char *street_name, int hour) {
  int total = 0;
  int count = 0;
  int i;
  for (i = 0; i < s->size; i++) {
    if (hour == s->info_array[i].hour &&
        strcmp(street_name, s->info_array[i].roadway_name) == 0) {
      count++;
      total += s->info_array[i].traffic;
    }
  }

  return total / count;
}
