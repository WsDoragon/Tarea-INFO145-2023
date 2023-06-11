CC = g++
CFLAGS = -std=c++11

all: programa

programa: p1_PD.cpp
	$(CC) $(CFLAGS) p1_PD.cpp -o programa

clean:
	rm -f programa
