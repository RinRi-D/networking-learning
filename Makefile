CC = gcc
CFLAGS = -O0
SRC = *.c

all: $(patsubst %.c, %.out, $(wildcard *.c))

%.out: %.c Makefile
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.out
