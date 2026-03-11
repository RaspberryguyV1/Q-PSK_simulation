#pragma once
#include <vector>
#include <bitset>
#include <string>
#include "alfabet.h"

class Encoder
{
private:
	Alphabet alfabet;
public:
	std::vector<std::bitset<2>> encode(std::string message);
};

