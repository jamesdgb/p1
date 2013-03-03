CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=hello


all: $(EXEC)

Debug: $(EXEC)

$(EXEC): main.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC) -o $@ -c $< $(CFLGAGS)

clean:
	rm -rf *.o
cleanDebug:clean

CleanRelease:Clean

mrproper: clean
	rm -rf $(EXEC)
