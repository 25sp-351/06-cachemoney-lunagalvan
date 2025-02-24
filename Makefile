CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
OBJECTS = main.o money_words.o

all: money_converter

money_converter: $(OBJECTS)
	$(CC) $(OBJECTS) -o money_converter

main.o: main.c money_words.h
	$(CC) $(CFLAGS) -c main.c

money_words.o: money_words.c money_words.h
	$(CC) $(CFLAGS) -c money_words.c

clean:
	rm -f *.o money_converter