#pragma once
#include <vector>
#include <bitset>
#include <string>
#include "alfabet.h"
class Decoder
{
private:
	Alphabet alfabet;
public:
	std::string decode(std::vector <std::bitset<2>> message);
};

