
CFLAGS = -std=c99 -Wall -Wextra

SRC = fs.c
HEADERS = fs.h
OBJS = $(SRC:.c=.o)

all: clean test

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

test: test.o $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)
	@./$@

clean:
	rm -f test $(OBJS)

.PHONY: test clean
