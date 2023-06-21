CC = g++
CFLAGS = -std=c++11

all: programaPD programaFB

programaPD: p1_PD.cpp
	$(CC) $(CFLAGS) p1_PD.cpp -o programaPD

programaFB: p1_fuerzaBruta.cpp
	$(CC) $(CFLAGS) p1_fuerzaBruta.cpp -o programaFB

clean:
	rm -f programaPD programaFB
