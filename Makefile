CC=g++
CFLAGS=-Wall -O2 -lgtest
SOURCES=test.cpp topsort.cpp
all: test
test: 
	$(CC) $(CFLAGS) -o test $(SOURCES)
clean:
	touch test
	rm test
run: test
	./test
remake: 
	make clean
	make all

