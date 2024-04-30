# Compiler to use
CC = gcc

# Flags to pass to the compiler
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50 -I../common

# Flags for linking, such as library paths and library names
LDFLAGS = -L../common -L../libcs50
LDLIBS = -lcommon -lcs50

# Name of the crawler executable
EXE = crawler

# Object files
OBJS = crawler.o pagedir.o

# Default target
all: $(EXE)

# Rule to link the program
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Rule to compile crawler.o
crawler.o: crawler.c pagedir.h
	$(CC) $(CFLAGS) -c crawler.c

# Rule to compile pagedir.o
pagedir.o: pagedir.c pagedir.h
	$(CC) $(CFLAGS) -c pagedir.c

# Phony targets for cleaning up
.PHONY: clean

clean:
	rm -f *~ *.o *.gch $(EXE)


