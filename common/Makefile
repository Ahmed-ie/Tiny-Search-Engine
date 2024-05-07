# common/Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50

# Object files and the target library
OBJS = pagedir.o index.o word.o
LIB = libcommon.a

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)
	ranlib $(LIB)

# Compilation rules for each module
pagedir.o: pagedir.c pagedir.h
	$(CC) $(CFLAGS) -c pagedir.c -o pagedir.o

index.o: index.c index.h
	$(CC) $(CFLAGS) -c index.c -o index.o

word.o: word.c word.h
	$(CC) $(CFLAGS) -c word.c -o word.o

# Phony target for cleaning up
.PHONY: clean

clean:
	rm -f $(LIB) *~ *.o
