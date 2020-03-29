CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS =

.PHONY: all clean

all: forests

forests: main.o parser.o agent.o bst.o
	$(CC) $(LDFLAGS) -o $@ $^

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c $<

agent.o: agent.c agent.h bst.h
	$(CC) $(CFLAGS) -c $<

parser.o: parser.c parser.h agent.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c parser.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o forests
