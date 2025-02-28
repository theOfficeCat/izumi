main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

clean:
	rm -f izumi main.o

all: main.o
	$(CC) $(CFLAGS) -o izumi main.o
