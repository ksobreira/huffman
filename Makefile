CC     = gcc
CFLAGS = -Wall -Wextra -g
SRC    = src/huffman.c src/heap.c src/compress.c src/decompress.c src/main.c
OBJ    = $(SRC:.c=.o)
TARGET = huffman

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) src/*.o