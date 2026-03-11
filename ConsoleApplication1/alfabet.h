#pragma once 
#include <string>
#include <iostream>#pragma once
class Alphabet {
private:
	const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .";

public:
	//Zdobycie indeksu litery
	int getIndex(char c) {
		int position = chars.find(c);
		if (position == std::string::npos) {
			//Kod spacji w razie b³êdu
			return 62;
		}
		return position;
	}
	//Metoda odwrotna
	char getChar(int index) {
		if (index < 0 || index >= chars.size()) 
		{
			return '?';
		}
		else 
		{ 
			return chars[index];
		}
		
		
	}
};