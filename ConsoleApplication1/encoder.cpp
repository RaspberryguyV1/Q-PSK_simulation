#include "encoder.h"
#include <iostream>

std::vector<std::bitset<2>> Encoder::encode(std::string message) {
	std::vector<std::bitset<2>> outputBits;

	std::bitset<2> syncSymbol(2); 

	//Kod pocz¹tku na start
	for (int i = 0; i < 4; i++) {
		outputBits.push_back(syncSymbol);
	}

	for (size_t i = 0; i < message.size(); i++)
	{
		char litera = message[i];
		int id = alfabet.getIndex(litera);
		std::bitset<8> litera_bin = id;

		for (int j = litera_bin.size() - 2; j >= 0; j = j - 2)
		{
			std::bitset<2> pair;
			pair[0] = litera_bin[j];
			pair[1] = litera_bin[j + 1];
			outputBits.push_back(pair);
		}
	}
	//Kod koñca na koniec
	for (int i = 0; i < 4; i++) {
		outputBits.push_back(syncSymbol);
	}
	return outputBits;
}