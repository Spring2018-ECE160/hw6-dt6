CC=gcc
CFLAGS=-I. -Wall -Werror -g

sort: main.c string_vector.h string_vector.o
	$(CC) $(CFLAGS) main.c string_vector.o -o sort

string_vector.o: string_vector.h string_vector.c
	$(CC) $(CFLAGS) -c string_vector.c -o string_vector.o
clean:
	rm sort string_vector.o

format:
	find . -name "*.[ch]" | xargs clang-format -style=Google -i
	
.PHONY: clean format
