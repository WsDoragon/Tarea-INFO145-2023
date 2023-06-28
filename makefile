CC = g++
CFLAGS = -std=c++11

all: programaFB programaPDV3 P2_Greedy P2_Ejemplo



programaFB: p1_fuerzaBruta.cpp
	$(CC) $(CFLAGS) p1_fuerzaBruta.cpp -o programaFB


programaPDV3: p1_PDV3.cpp
	$(CC) $(CFLAGS) p1_PDV3.cpp -o programaPDV3


P2_Greedy: P2_Greedy.cpp
	$(CC) $(CFLAGS) P2_Greedy.cpp -o P2_Greedy

P2_Ejemplo: p2_Ejemplo.cpp
	$(CC) $(CFLAGS) p2_Ejemplo.cpp -o P2_ejemplo


clean:
	rm -f programaPD programaFB
