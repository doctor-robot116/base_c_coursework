CC = gcc
CFLAGS = -Wall -g

temp_stats: main.o temp_functions.o
	$(CC) $(CFLAGS) main.o temp_functions.o -o temp_stats

main.o: main.c temp_functions.h
	$(CC) $(CFLAGS) -c main.c

temp_functions.o: temp_functions.c temp_functions.h
	$(CC) $(CFLAGS) -c temp_functions.c

clean:
	rm -f *.o temp_stats