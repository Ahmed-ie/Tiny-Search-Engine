# indexer/Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common -I../libcs50
LDFLAGS = -L../common -L../libcs50
LDLIBS = -lcommon -lcs50

# Executables to be built
EXECS = indexer indextest

# Object files for each executable
INDEXER_OBJS = indexer.o
INDEXTEST_OBJS = indextest.o

# Default target builds both executables
all: $(EXECS)

# Rule for building indexer
indexer: $(INDEXER_OBJS)
	$(CC) $(CFLAGS) $(INDEXER_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Rule for building indextest
indextest: $(INDEXTEST_OBJS)
	$(CC) $(CFLAGS) $(INDEXTEST_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# Object file compilation rules
indexer.o: indexer.c ../common/index.h ../common/pagedir.h ../common/word.h ../libcs50/hashtable.h ../libcs50/counters.h
	$(CC) $(CFLAGS) -c indexer.c -o indexer.o

indextest.o: indextest.c ../common/index.h ../libcs50/file.h
	$(CC) $(CFLAGS) -c indextest.c -o indextest.o

# Phony targets for testing, cleaning, etc.
.PHONY: clean test

clean:
	rm -f *.o $(EXECS)


test:
	./testing.sh &> testing.out
