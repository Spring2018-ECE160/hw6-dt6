CC=gcc
CFLAGS=-I. -Wall -Werror

question1: main.c
	$(CC) $(CFLAGS) main.c -o question1

clean:
	rm question1

format:
	find . -name "*.[ch]" | xargs clang-format -style=Google -i
	
.PHONY: clean format
