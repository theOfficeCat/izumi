PROJECT := izumi
BINARY := izumi
CC := gcc
CFLAGS := -Wall -pedantic -g -O0 `pkg-config --cflags ncurses`
LDFLAGS := -lm `pkg-config --libs ncurses`

SRC := $(wildcard src/*.c)
HDR := $(wildcard src/*.h)
OBJ := $(patsubst %.c,%.o,$(SRC))

all: $(BINARY)

$(BINARY): $(OBJ)
	$(CC) -o $(BINARY) $(OBJ) $(LDFLAGS)

%.o: src/%.c $(HDR)
	$(CC) -c $(CFLAGS) $<

.PHONY: clean
clean:
	rm $(BINARY) src/*.o