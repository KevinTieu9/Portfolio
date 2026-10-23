# lockbox
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
BIN = lockbox

all: $(BIN)

$(BIN): main.c env.c vault.c log.c copy.c commands.c screen.c index.c process.c
	$(CC) $(CFLAGS) -o $(BIN) main.c env.c vault.c log.c copy.c commands.c screen.c index.c process.c -lncurses

clean:
	rm -f $(BIN)
