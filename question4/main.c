#include <stdio.h>
#include <stdlib.h> // atoi
#define MAX_INPUT_LENGTH 1024

typedef struct point {
  int x;
  int y;
} point;

// Prompt user for constants a, b & c.
void prompt_user(int *a, int *b, int *c);

// Calculate y value of quadratic curve.
int calculate_y(int a, int b, int c, int x);

void print_curve(int a, int b, int c);

void print_point(point p);

int main(){
  int a, b, c;
  prompt_user(&a, &b, &c);
  print_curve(a, b, c);
  return 0;
}

void prompt_user(int *a, int *b, int *c){
  char input[MAX_INPUT_LENGTH];
  printf("Enter a:");
  fgets(input, MAX_INPUT_LENGTH, stdin);
  *a = atoi(input);
  printf("Enter b:");
  fgets(input, MAX_INPUT_LENGTH, stdin);
  *b = atoi(input);
  printf("Enter c:");
  fgets(input, MAX_INPUT_LENGTH, stdin);
  *c = atoi(input);
}

int calculate_y(int a, int b, int c, int x){
  return a*x*x+b*x+c;
}

void print_curve(int a, int b, int c){
  point curve[11];
  int i;
  for(i = 0; i <11; i++){
    curve[i].x = i-5;
    curve[i].y = calculate_y(a, b, c, curve[i].x);
  }
  for(i=0; i<11;i++){
    print_point(curve[i]);
  }
}

void print_point(point p){
  printf("(%d, %d)\n", p.x, p.y);
}
