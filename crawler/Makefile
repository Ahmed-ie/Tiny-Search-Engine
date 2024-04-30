CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50 -I../common
CC = gcc
LIBS = ../libcs50/libcs50.a

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: clean test

crawler: crawler.o ../common/pagedir.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: crawler.c ../libcs50/webpage.h ../libcs50/hashtable.h ../libcs50/bag.h ../common/pagedir.h
	$(CC) $(CFLAGS) -c crawler.c -o crawler.o

../common/pagedir.o: ../common/pagedir.c ../common/pagedir.h
	$(CC) $(CFLAGS) -c ../common/pagedir.c -o ../common/pagedir.o

test: 
	./testing.sh &> testing.out

clean:
	rm -rf testing.out
	rm -rf $(shell ls | grep "^test[0-9]*$$")
	rm -rf *.x *.o

