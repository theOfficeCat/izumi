all: main.o parser.o
	$(CC) $(CFLAGS) -o izumi main.o parser.o

parser.o: src/parser.c
	$(CC) $(CFLAGS) -c src/parser.c

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

clean:
	rm -f izumi *.o

