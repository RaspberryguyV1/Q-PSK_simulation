#include "decoder.h"
#include <vector>
#include <bitset>
#include <string>
#include <iostream>

std::string Decoder::decode(std::vector <std::bitset<2>> message) {
	std::string odebranaWiad ="";
	
	for (int i = 4; i + 4 < message.size(); i=i+4)//Pomijamy pocz¹tkowe i koñcowe bity
	{
		std::bitset<8> symbol;
		symbol[7] = message[i][1];
		symbol[6] = message[i][0];

		symbol[5] = message[i+1][1];
		symbol[4] = message[i+1][0];

		symbol[3] = message[i+2][1];
		symbol[2] = message[i+2][0];

		symbol[1] = message[i+3][1];
		symbol[0] = message[i+3][0];
		odebranaWiad += alfabet.getChar((int)symbol.to_ulong());
	}
	return odebranaWiad;
}