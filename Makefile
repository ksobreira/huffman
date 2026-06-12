CC     = gcc
CFLAGS = -Wall -Wextra -g
SRC    = src/huffman.c src/heap.c src/compress.c src/decompress.c src/main.c
TARGET = bin/huffman

all: bin $(TARGET)

bin:
	mkdir -p bin

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -rf bin