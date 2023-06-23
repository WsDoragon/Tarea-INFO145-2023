CC = g++
CFLAGS = -std=c++11

all: programaPD programaFB programaPDV2 programaP2

programaPD: p1_PD.cpp
	$(CC) $(CFLAGS) p1_PD.cpp -o programaPD

programaFB: p1_fuerzaBruta.cpp
	$(CC) $(CFLAGS) p1_fuerzaBruta.cpp -o programaFB

programaPDV2: p1_PDV2.cpp
	$(CC) $(CFLAGS) p1_PDV2.cpp -o programaPDV2

programaP2: p2.cpp
	$(CC) $(CFLAGS) p2.cpp -o programaP2


clean:
	rm -f programaPD programaFB
