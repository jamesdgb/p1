CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=hello


all: $(EXEC)

hello: main.o
	$(CC) -o $@ $^ $(LDFLAGS)
main.o: main.c
	$(CC) -o $@ -c $< $(CFLGAGS)
clean:	
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)
