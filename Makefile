CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=hello
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

Debug: $(EXEC)

hello: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: socket.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLGAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

cleanDebug:mrproper

CleanRelease:mrproper

mrproper: clean
	rm -rf $(EXEC)
