
all: clean test

clean:
	rm -f test-fs

test:
	$(CC) --std=c99 test.c -o test-fs
	./test-fs

.PHONY: clean test
