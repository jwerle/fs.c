CFLAGS?=--std=c99

all: clean test

clean:
	rm -f test-fs *.o

test: fs.o
	$(CC) ${CFLAGS} test.c fs.o -o test-fs
	./test-fs

.PHONY: clean test
