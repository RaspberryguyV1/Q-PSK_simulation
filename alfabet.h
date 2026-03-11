#pragma once 
#include <string>

class alphabet {

public:
	int getIndex(char c) {
		// Rzutujemy na unsigned char, ¿eby polskie znaki/specjalne
		// mia³y wartoœci 128-255, a nie ujemne.
		return (unsigned char)c;
	}

	// Indeks (0-255) -> Znak
	char getChar(int index) {
		return (char)index;
	}
};