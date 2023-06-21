CC = g++
CFLAGS = -std=c++11

all: programaPD programaFB programaPDV2

programaPD: p1_PD.cpp
	$(CC) $(CFLAGS) p1_PD.cpp -o programaPD

programaFB: p1_fuerzaBruta.cpp
	$(CC) $(CFLAGS) p1_fuerzaBruta.cpp -o programaFB

programaPD: p1_PDV2.cpp
	$(CC) $(CFLAGS) p1_PDV2.cpp -o programaPDV2

clean:
	rm -f programaPD programaFB
