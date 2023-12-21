# Example makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = myprogram
SOURCE = myprogram.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
