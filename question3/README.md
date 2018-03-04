## Question 2

(K&R Exercise 5-14 & 5-15) Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n.

Also, add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting; for example, a and A compare equal.

Compile Steps:
`make`  
Output:
```
./sort sample.txt
2 cents
Animal
C PROGRAMMING LANGUAGE
Gnome
Poland
Qt
Steel Construction Manual
application
olive oil
playing card
salt
wrapper
```
```
./sort sample.txt -f
2 cents
Animal
application
C PROGRAMMING LANGUAGE
Gnome
olive oil
playing card
Poland
Qt
salt
Steel Construction Manual
wrapper
```
```
./sort sample.txt -r
wrapper
salt
playing card
olive oil
application
Steel Construction Manual
Qt
Poland
Gnome
C PROGRAMMING LANGUAGE
Animal
2 cents
```
```
./sort -r sample.txt -f
wrapper
Steel Construction Manual
salt
Qt
Poland
playing card
olive oil
Gnome
C PROGRAMMING LANGUAGE
application
Animal
2 cents
```
