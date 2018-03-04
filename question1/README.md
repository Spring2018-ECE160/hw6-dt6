## Question 1

Write a funciton that determines the maximum and minimum values from a one-dimensional array. Assume that the corresponding function prototype statement is

<code>void ranges(int x[], int npts, int *max_ptr, int *min_ptr)</code>

where npts contain the number of values in array x, and max_ptr and min_ptr are pointers to the variables in which to store the maximum and minimum values in the array.

Provide and print out 3 examples to show that your function is working as intended.

Compile Steps: 
`make`  
Output:
```
./question1 7
MIN: 7
MAX: 7
```
```
./question1 1 2 3 4 5 6
MIN: 1
MAX: 6
```
```
./question1 -123 22 13 2
MIN: -123
MAX: 22
```
