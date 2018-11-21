CC=gcc
CFLAGS=-Wall -pedantic
LD=gcc
LIBS=-lm -lSDL2


all: clock

clock: main.o analog.o digital.o geeky.o
	$(LD) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main.o analog.o digital.o geeky.o clock core *~

analog.o: analog.c analog.h
digital.o: digital.c digital.h
geeky.o: geeky.c geeky.h
main.o: main.c analog.h digital.h geeky.h
