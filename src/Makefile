CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lsqlite3

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
BIN = server

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(BIN)
