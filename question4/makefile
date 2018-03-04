CC=gcc
CFLAGS=-I. -Wall -Werror

question4: main.c
	$(CC) $(CFLAGS) main.c -o question4

clean:
	rm question4

format:
	find . -name "*.[ch]" | xargs clang-format -style=Google -i
	
.PHONY: clean format
