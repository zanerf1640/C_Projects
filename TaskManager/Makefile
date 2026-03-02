CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
SOURCES = src/main.c src/task.c src/file_io.c src/ui.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = task_manager

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
