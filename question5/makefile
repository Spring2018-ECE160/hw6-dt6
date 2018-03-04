CC=gcc
CFLAGS=-I. -Wall -Werror

trafficanalysis: main.c
	$(CC) $(CFLAGS) main.c -o trafficanalysis

clean:
	rm trafficanalysis

format:
	find . -name "*.[ch]" | xargs clang-format -style=Google -i
	
.PHONY: clean format
