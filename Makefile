CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

all: bin/worker bin/os_manager

bin/worker: src/worker.c
	$(CC) $(CFLAGS) src/worker.c -o bin/worker

bin/os_manager: src/main.c src/process_manager.c include/process_manager.h
	$(CC) $(CFLAGS) src/main.c src/process_manager.c -o bin/os_manager

clean:
	rm -f bin/worker bin/os_manager
