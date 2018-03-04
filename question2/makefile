CC=gcc
CFLAGS=-I. -Wall -Werror

tail: tail.c queue.o
	$(CC) $(CFLAGS) tail.c queue.o -o tail

queue.o: queue.h queue.c
	$(CC) $(CFLAGS) -c queue.c -o queue.o

clean:
	rm tail

format:
	find . -name "*.[ch]" | xargs clang-format -style=Google -i
	
.PHONY: clean format
