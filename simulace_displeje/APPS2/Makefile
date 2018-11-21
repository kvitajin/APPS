CFLAGS+=$(shell pkg-config --cflags opencv)
LDFLAGS+=$(shell pkg-config --libs opencv)

all: main

main: main.cpp
	g++ main.cpp -o $@ $(CFLAGS) $(LDFLAGS)

clean: 
	rm -rf main

